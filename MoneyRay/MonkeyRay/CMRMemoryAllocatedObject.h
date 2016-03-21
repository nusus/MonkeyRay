#ifndef CMRMemoryAllocatedObject_h__
#define CMRMemoryAllocatedObject_h__


namespace MR
{
	template < typename Alloc>
	class CMRAllocatedObject
	{
	public:
		explicit CMRAllocatedObject() {}
		~CMRAllocatedObject() {}

		void* operator new(std::size_t sz)
		{
			return Alloc::Allocate(sz);
		}

		void* operator new(std::size_t sz, void* ptr)
		{
			(void)sz;
			return ptr;
		}

		void* operator new[](std::size_t sz)
		{
			return Alloc::Allocate(sz);
		}

		void operator delete(void* ptr)
		{
			Alloc::Deallocate(ptr);
		}

		void operator delete(void * ptr, void*)
		{
			Alloc::Deallocate(ptr);
		}


		void operator delete[](void* ptr)
		{
			Alloc::Deallocate(ptr);
		}

	protected:
	private:
	};
}
#endif // CMRMemoryAllocatedObject_h__
