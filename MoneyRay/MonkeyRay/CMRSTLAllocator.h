#ifndef CMRSTLAllocator_h__
#define CMRSTLAllocator_h__

namespace MR
{
	template <typename T>
	struct CMRSTLAllocatorBase 
	{
		typedef T value_type;
	};

	template <typename T>
	struct CMRSTLAllocatorBase<const T> 
	{
		typedef T value_type;
	};

	template<typename T1, typename T2>
	inline void ConstructAux(T1* ptr, const T2& value)
	{
		new(ptr) T1(value);
	}

	template <typename T, typename AllocPolicy>
	class CMRSTLAllocator : public CMRSTLAllocatorBase<T>
	{
	public:
		//STL Allocator标准的类型定义
		typedef CMRSTLAllocatorBase<T>	Base;
		typedef typename Base::value_type		value_type;
		typedef value_type*						pointer;
		typedef const value_type*				const_pointer;
		typedef value_type&						reference;
		typedef const value_type&				const_reference;
		typedef std::size_t						size_type;
		typedef std::ptrdiff_t					difference_type;

		//rebind allocator for type U
		template <typename U>
		struct rebind 
		{
			typedef CMRSTLAllocator<U> other;
		};

		inline explicit CMRSTLAllocator() {}

		virtual ~CMRSTLAllocator() {}

		inline CMRSTLAllocator(const CMRSTLAllocator& allocator) {}

		template <typename U>
		inline CMRSTLAllocator(const CMRSTLAllocator<U, AlloPolicy>&) {}

		template <typename U, typename P>
		inline CMRSTLAllocator(const CMRSTLAllocator<U, P>&) {}

		inline pointer allocate(size_type n, const void* hint = 0) 
		{
			register size_type bytes_count = n * sizeof(T);
			pointer ret = static_cast<pointer>(AllocPolicy::Allocate(bytes_count));
			return ret;
		}

		inline void deallocate(pointer ptr, size_type n)
		{
			AllocPolicy::Deallocate(ptr);
		}

		pointer address(reference x) const
		{
			return (pointer)&x;
		}

		const_pointer const_address(const_reference x) const
		{
			return (const_pointer)&x;
		}

		void construct(pointer ptr)
		{
			::ConstructAux(ptr, value_type());
		}

		void construct(pointer ptr, const value_type& value)
		{
			::ConstructAux(ptr, value);
		}

		void destroy(pointer p)
		{
			p->~value_type();
		}

		size_type max_size() const throw()
		{
			return AllocPolicy::GetMaxAllocationSize();
		}
	};

	template <typename T1, typename T2, typename AllocPolicy>
	inline bool operator==(
		const CMRSTLAllocator<T1, AllocPolicy>&,
		const CMRSTLAllocator<T2, AllocPolicy>&
		) 
	{
		return true;
	}

	template <typename T1, typename T2, typename AllocPolicy>
	inline bool operator!=(
		const CMRSTLAllocator<T1, AllocPolicy>,
		const CMRSTLAllocator<T2, AllocPolicy>
		)
	{
		return false;
	}

	template <typename T1, typename AllocPolicy, typename OtherAllocator>
	inline bool operator==(
		const CMRSTLAllocator<T1, AllocPolicy>,
		const OtherAllocator
		)
	{
		return false;
	}

	template <typename T1, typename AllocPolicy, typename OtherAllocator>
	inline bool operator!=(
		const CMRSTLAllocator<T1, AllocPolicy>,
		const OtherAllocator
		)
	{
		return true;
	}
}
#endif // CMRAllocator_h__
