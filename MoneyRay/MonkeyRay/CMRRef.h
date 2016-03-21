#ifndef CMRRef_h__
#define CMRRef_h__

#include "CMRMemoryAllocatorConfig.h"
#include <thread>
#include <mutex>

namespace MR
{
	class CMRMemManager;
	class CMRSubsciber;
	class CMRSubsciption;
	class CMRRef : public CMRObjectBase
	{
	public:

		CMRRef();

		CMRRef(const CMRRef& obj) :
			m_RefMutex(),
			m_nRefCount(0),
			m_pSubsciption(0) {}
		inline CMRRef& operator = (const CMRRef&) { return *this; }

		static std::mutex* GetGlobalReferenceMutex();

		inline int Retain() const;

		inline int Release() const;

		int ReleaseNoDelete() const;

		inline int ReferenceCount() const { return m_nRefCount; }

		CMRSubsciption* GetSubscription() const { return static_cast<CMRSubsciption*>(m_pSubsciption); }

		CMRSubsciption* GetOrCreateSubscription() const;

		void AddSubcriber(CMRSubsciber* subsciber) const;

		void RemoveSubsciber(CMRSubsciber* subscriber) const;

#ifdef NOT_FORCE_USE_THREAD_SAFE_IN_OBJECT
		explicit CMRRef(bool bThreadSafeRefUnref);
		virtual void SetThreadSafeRefUnref(bool bThreadSafe);
		bool GetThreadSafeRefUnref() const { return ((bool)m_RefMutex); }
		static void SetThreadSafeReferenceCounting(bool bEnableThreadSafeReferenceCounting);
		static bool GetThreadSafeReferenceCounting();
#endif // NOT_FORCE_USE_THREAD_SAFE_IN_OBJECT	
	public:
		friend class CMRMemManager;

		static CMRMemManager* GetMemManager();
	protected:
		virtual ~CMRRef();
		void SignalObserversToDelete() const;
		void MemManagerDelete() const;
	protected:
		//TODO: 注意，这里的mutex可以考虑使用自定义的内存分配器进行内存分配
		mutable std::mutex			m_RefMutex;
		mutable int					m_nRefCount;
		mutable void*				m_pSubsciption;
	};
}
#endif // CMRRef_h__
