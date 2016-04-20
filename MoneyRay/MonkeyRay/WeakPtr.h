#ifndef WeakPtr_h__
#define WeakPtr_h__ 
#include "SmartPtr.h"
#include "CMRObserver.h"

#include <thread>
namespace MR
{
	//weak pointer called as weak_ptr in the stl
	template<class T>
	class WeakPtr
	{
	public:
		//constructors for the WeakPtr
		typedef T element_type;
		WeakPtr() : m_subscription(0), m_ptr(0) {}

		WeakPtr(const SmartPtr<T>& rp)
		{
			m_subscription = rp.Valid() ? rp->GetOrCreateSubscription() : 0;
			m_ptr = (m_subscription.Valid() && m_subscription->GetPublisher() != 0) ? rp.Get() : 0;
		}

		WeakPtr(T* rp)
		{
			m_subscription = rp ? rp->GetOrCreateSubscription() : 0;
			m_ptr = (m_subscription.Valid() && m_subscription->GetPublisher() != 0) ? rp : 0;
		}

		WeakPtr(const WeakPtr& wp) :
			m_subscription(wp.m_subscription),
			m_ptr(wp.m_ptr)
		{
		}

		//destructors
		~WeakPtr()
		{
		}

		//specified for the copy operator
		WeakPtr& operator = (const WeakPtr& wp)
		{
			if (&wp == this) return *this;

			m_subscription = wp.m_subscription;
			m_ptr = wp.m_ptr;
			return *this;
		}

		WeakPtr& operator = (const SmartPtr<T>& rp)
		{
			m_subscription = rp.Valid() ? rp->GetOrCreateSubscription() : 0;
			m_ptr = (m_subscription.Valid() && m_subscription->GetPublisher() != 0) ? rp.Get() : 0;
			return *this;
		}

		WeakPtr& operator = (T* rp)
		{
			m_subscription = rp ? rp->GetOrCreateSubscription() : 0;
			m_ptr = (m_subscription.Valid() && m_subscription->GetPublisher() != 0) ? rp : 0;
			return *this;
		}

		//when used in the multi-thread situation, we should assign the WeakPtr to the SmartPtr
		bool Lock(SmartPtr<T>& rptr) const
		{
			if (!m_subscription)
			{
				rptr = 0;
				return false;
			}

			CMRRef* obj = m_subscription->AddRefLock();
			if (!obj)
			{
				rptr = 0;
				return false;
			}

			rptr = m_ptr;
			obj->ReleaseNoDelete();
			return rptr.Valid();
		}

		//override the relational operator
		bool operator == (const WeakPtr& wp) const { return m_subscription == wp.m_subscription; }
		bool operator != (const WeakPtr& wp) const { return m_subscription != wp.m_subscription; }
		bool operator < (const WeakPtr& wp) const { return m_subscription < wp.m_subscription; }
		bool operator > (const WeakPtr& wp) const { return m_subscription > wp.m_subscription; }

		inline bool operator == (const T* ptr) const { return m_ptr == ptr; }
		inline bool operator != (const T* ptr) const { return m_ptr != ptr; }
		inline bool operator < (const T* ptr) const { return m_ptr < ptr; }
		inline bool operator > (const T* ptr) const { return m_ptr > ptr; }

		//override the operator used in the raw pointer
		inline T& operator*() const { return *m_ptr; }
		inline T* operator->() const { return m_ptr; }

		//get the raw pointer
		inline T* Get() const { return (m_subscription.Valid() && m_subscription->GetPublisher() != 0) ? m_ptr : 0; }

		//override the ! operator
		inline bool operator!() const { return Get() == nullptr; }

		//check whether the raw pointer held by this WeakPtr is nullptr
		inline bool Valid() const { return Get() != nullptr; }

	protected:

		SmartPtr<CMRSubsciption>   m_subscription;
		T*                          m_ptr;
	};

	
}
#endif // WeakPtr_h__
