#ifndef CMRMemoryAllocatorConfig_h__
#define CMRMemoryAllocatorConfig_h__

#include "CMRConfig.h"
#include "CMRMemoryNedPooling.h"
namespace MR
{
	//define the real aligned memory policy for the STL component
	typedef CMRMemoryNedPoolingAlignedPolicy<MR_MEMORY_NED_POOLING_ALIGNMENT> CMRMemRealAlignedPolicy;

#if MR_MEMORY_STL_ALLOCATOR_IS_ALIGNED == MR_MEMORY_STL_ALLOCATOR_USE_ALIGNED
	typedef CMRMemRealAlignedPolicy CMRMemSTLAllocatorPolicy;
#else
	typedef CMRMemoryNedPoolingPolicy CMRMemSTLAllocatorPolicy;
#endif

#if MR_MEMORY_ALLOCATE_OBJECT_IS_ALIGNED == MR_MEMORY_ALLOCATE_OBJECT_USE_ALIGNED
	typedef CMRMemRealAlignedPolicy CMRObjAllocatorPolicy;
#else
	typedef CMRMemoryNedPoolingPolicy CMRObjAllocatorPolicy;
#endif
	//alias template for the allocator that will be used in the STL component
	template<
		typename T,
		typename Policy = CMRMemSTLAllocatorPolicy
	>
		using STLAllocator = CMRSTLAllocator<T, Policy>;

	/************************************************************************/
	/* we should always use CMRObjectFactory instead of new/delete to instantiation a object.
		Note:using new and delete to allocate memory will lead to memory leaking. 
	*/
	/************************************************************************/
	template <typename AllocPolicy = CMRObjAllocatorPolicy>
	class CMRObjectFactory
	{
	public:
		class CMRSharedPtrDeleter
		{
		public:
			template <typename T>
			void operator()(T* ptr)
			{
				AllocPolicy::Deallocate(ptr);
			}
		};

		class CMRUniquePtrDeleter
		{
		public:
			template <typename T>
			void operator()(T* ptr)
			{
				AllocPolicy::Deallocate(ptr);
			}
		};
	public:
		template <typename T, typename... Args>
		static shared_ptr<T> CreateSharedPtr(Args&&... args)
		{
			T* ptr= static_cast<T*>(AllocPolicy::Allocate(sizeof(T), MR_MEMORY_NED_POOLING_ALIGNMENT));
			::new(ptr) T(std::forward<Args>(args)...);
			return shared_ptr(ptr, ::CMRSharedPtrDeleter(), STLAllocator<T>());
		}

		template <typename T, typename... Args>
		static unique_ptr<T, CMRUniquePtrDeleter> CreateUniquePtr(Args&&... args)
		{
			T* ptr = static_cast<T*>(AllocPolicy::Allocate(sizeof(T), MR_MEMORY_NED_POOLING_ALIGNMENT));
			::new(ptr) T(std::forward<Args>(args)...);
			return unique_ptr(ptr);
		}

		static void* Malloc(std::size_t bytes)
		{
			return AllocPolicy::Allocate(bytes);
		}

		static void Free(void* ptr)
		{
			AllocPolicy::Deallocate(ptr);
		}

		template <typename T>
		static void* MallocN(std::size_t nCount)
		{
			return AllocPolicy::Allocate(sizeof<T> * nCount);
		}

	};
}
#endif // CMonkeyRayMemoryAllocatorConfig_h__
