#ifndef SmartPtr_h__
#define SmartPtr_h__

namespace MR
{
	template<typename T> class WeakPtr;

	//reference counting smart pointer called shared_ptr in the stl
	template<class T>
	class SmartPtr
	{
	public:
		typedef T element_type;
	public:
		//constructors
		SmartPtr() 
			: m_ptr(0) 
		{}

		SmartPtr(T* ptr) 
			: m_ptr(ptr) 
		{ 
			if (m_ptr) m_ptr->Retain(); 
		}

		SmartPtr(const SmartPtr& rp) 
			: m_ptr(rp.m_ptr) 
		{ 
			if (m_ptr) m_ptr->Retain(); 
		}

		template<class Other>
		SmartPtr(const SmartPtr<Other>& rp) 
			: m_ptr(rp.m_ptr) 
		{ 
			if (m_ptr) m_ptr->Retain(); 
		}

		SmartPtr(WeakPtr<T>& optr) 
			: m_ptr(0) 
		{ 
			optr.Lock(*this); 
		}

		//destructor
		~SmartPtr() 
		{ 
			if (m_ptr) m_ptr->Release();  
			m_ptr = 0; 
		}

		//specified for the copy operator
		SmartPtr& operator = (const SmartPtr& rp)
		{
			Assign(rp);
			return *this;
		}

		template<class Other> SmartPtr& operator = (const SmartPtr<Other>& rp)
		{
			Assign(rp);
			return *this;
		}

		inline SmartPtr& operator = (T* ptr)
		{
			if (m_ptr == ptr) return *this;
			T* tmpm_ptr = m_ptr;
			m_ptr = ptr;
			if (m_ptr) m_ptr->Retain();
			if (tmpm_ptr) tmpm_ptr->Release();
			return *this;
		}

		//relational operator
		bool operator == (const SmartPtr& rp) const { return (m_ptr == rp.m_ptr); }
		bool operator == (const T* ptr) const { return (m_ptr == ptr); }
		friend bool operator == (const T* ptr, const SmartPtr& rp) { return (ptr == rp.m_ptr); }

		bool operator != (const SmartPtr& rp) const { return (m_ptr != rp.m_ptr); }
		bool operator != (const T* ptr) const { return (m_ptr != ptr); }
		friend bool operator != (const T* ptr, const SmartPtr& rp) { return (ptr != rp.m_ptr); }

		bool operator < (const SmartPtr& rp) const { return (m_ptr < rp.m_ptr); }

	public:

		//operator also used in the raw pointer
		T& operator*() const { return *m_ptr; }
		T* operator->() const { return m_ptr; }

		//get the raw pointer
		T* Get() const { return m_ptr; }

		//bool operation
		bool operator!() const { return m_ptr == 0; } 
		bool Valid() const { return m_ptr != 0; }

		//used just before returning the raw pointer in the function. 
		T* Release() 
		{ 
			T* tmp = m_ptr; 
			if (m_ptr) m_ptr->ReleaseNoDelete();
			//set m_ptr to nullptr, avoid automatic memory management when leaving the scope.
			m_ptr = 0;
			return tmp; 
		}

		void Swap(SmartPtr& rp) 
		{ 
			T* tmp = m_ptr; 
			m_ptr = rp.m_ptr; 
			rp.m_ptr = tmp; 
		}

	private:

		template<class Other> void Assign(const SmartPtr<Other>& rp)
		{
			if (m_ptr == rp.m_ptr) return;
			T* tmp_ptr = m_ptr;
			m_ptr = rp.m_ptr;
			if (m_ptr) m_ptr->Retain();
			if (tmp_ptr) tmp_ptr->Release();
		}

		template<class Other> friend class SmartPtr;

		T* m_ptr;
	};


	template<class T> inline
		void Swap(SmartPtr<T>& rp1, SmartPtr<T>& rp2) { rp1.Swap(rp2); }

	template<class T> inline
		T* GetPointer(const SmartPtr<T>& rp) { return rp.Get(); }

	template<class T, class Y> inline
		SmartPtr<T> static_pointer_cast(const SmartPtr<Y>& rp) { return static_cast<T*>(rp.Get()); }

	template<class T, class Y> inline
		SmartPtr<T> dynamic_pointer_cast(const SmartPtr<Y>& rp) { return dynamic_cast<T*>(rp.Get()); }

	template<class T, class Y> 
	inline SmartPtr<T> const_pointer_cast(const SmartPtr<Y>& rp) 
	{ 
		return const_cast<T*>(rp.Get()); 
	}

}
#endif // SmartPtr_h__
