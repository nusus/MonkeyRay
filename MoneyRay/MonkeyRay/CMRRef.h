#ifndef CMRRef_h__
#define CMRRef_h__

#include "CMRPrerequisites.h"
#if MR_USE_MULTITHREAD
#include <mutex>
#endif

namespace MR
{
	class CMRMemManager;

	class CMRRef : public CMRObjectBase
	{
	public:

		CMRRef();

		CMRRef(const CMRRef& obj);
		CMRRef& operator = (const CMRRef&);

#if MR_USE_MULTITHREAD
		static std::mutex* GetGlobalReferenceMutex();
#endif

		inline int Retain() const;

		inline int Release() const;

		int ReleaseNoDelete() const;

		int ReferenceCount() const;

#ifdef NOT_FORCE_USE_THREAD_SAFE_IN_OBJECT
		explicit CMRRef(bool bThreadSafeRefUnref);
		virtual void SetThreadSafeRefUnref(bool bThreadSafe);
		bool GetThreadSafeRefUnref() const;
		static void SetThreadSafeReferenceCounting(bool bEnableThreadSafeReferenceCounting);
		static bool GetThreadSafeReferenceCounting();
#endif // NOT_FORCE_USE_THREAD_SAFE_IN_OBJECT	
	public:
		friend class CMRMemManager;

		static CMRMemManager* GetMemManager();
	protected:
		virtual ~CMRRef();
		void MemManagerDelete() const;
	protected:
#if MR_USE_MULTITHREAD
		//TODO: 注意，这里的mutex可以考虑使用自定义的内存分配器进行内存分配
		mutable std::mutex			m_RefMutex;
#endif
		mutable int					m_nRefCount;
	};
}
#endif // CMRRef_h__
