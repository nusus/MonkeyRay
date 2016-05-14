#ifndef CMRMemoryNedPooling_h__
#define CMRMemoryNedPooling_h__

#include <limits>
namespace MR
{
	class CMRMemoryNedPoolingAux
	{
	public:
		static void* Allocate(size_t count);
		static void Deallocate(void* ptr);
		static void* AllocateAligned(size_t count, size_t alignment);
		static void DeallocateAligned(void* ptr, size_t alignment);
	};

	class CMRMemoryNedPoolingPolicy
	{
	public:
		static inline void* Allocate(size_t count)
		{
			return CMRMemoryNedPoolingAux::Allocate(count);
		}

		static inline void Deallocate(void* ptr)
		{
			CMRMemoryNedPoolingAux::Deallocate(ptr);
		}

		static inline size_t GetMaxAllocationSize()
		{
			return std::numeric_limits<size_t>::max();
		}
		CMRMemoryNedPoolingPolicy() = delete;
	};

	template <size_t Alignment = 0 >
	class CMRMemoryNedPoolingAlignedPolicy
	{
	public:
		//在编译期检查Alignment是否是合法的
		typedef int CheckAlignment[Alignment <= 128 && ((Alignment & (Alignment - 1)) == 0) ? +1 : -1];
		
		static inline void* Allocate(size_t count)
		{
			return CMRMemoryNedPoolingAux::AllocateAligned(count, Alignment);
		}

		static inline void Deallocate(void* ptr)
		{
			CMRMemoryNedPoolingAux::DeallocateAligned(ptr, Alignment);
		}

		static inline size_t GetMaxAllocationSize()
		{
			return std::numeric_limits<int>::max();
		}
	
		CMRMemoryNedPoolingAlignedPolicy() = delete;
	private:

	};

}
#endif // CMRMemoryNedPooling_h__
