#include "CMRRef.h"
#include <assert.h>
#include "CMRMemManager.h"
#include "CMRObserver.h"

using namespace MR;

#if MR_USE_MULTITHREAD
std::mutex* MR::CMRRef::GetGlobalReferenceMutex()
{
	static std::shared_ptr<std::mutex> s_GlobalRefMutex = std::make_shared<std::mutex>();
	return s_GlobalRefMutex.get();
}
#endif

MR::CMRMemManager* MR::CMRRef::GetMemManager()
{

	static std::shared_ptr<MR::CMRMemManager> s_MemManager = std::make_shared<MR::CMRMemManager>(1);
	return s_MemManager.get();
}


struct SMRInit
{
	SMRInit()
	{
#if MR_USE_MULTITHREAD
		MR::CMRRef::GetGlobalReferenceMutex();
#endif
		MR::CMRRef::GetMemManager();
	}
};

static SMRInit s_initGlobalMutex;


MR::CMRRef::CMRRef():
#if MR_USE_MULTITHREAD
	m_RefMutex(),
#endif
	m_nRefCount(0)
{

}



CMRRef& MR::CMRRef::operator=(const CMRRef&)
{
	return *this;
}

MR::CMRRef::~CMRRef()
{

}


int MR::CMRRef::Retain() const
{

#if MR_USE_MULTITHREAD
	std::lock_guard<std::mutex> lck(m_RefMutex);
#endif
	return ++m_nRefCount;
}

int MR::CMRRef::Release() const
{
	unsigned int new_ref_count;
	bool bDelete = false;
	{
#if MR_USE_MULTITHREAD
		std::lock_guard<std::mutex> lck(m_RefMutex);
#endif
		assert(m_nRefCount > 0);
		if (m_nRefCount <= 0)
		{
			return 0;
		}
		new_ref_count = --m_nRefCount;
		if (new_ref_count == 0)
		{
			bDelete = true;
		}
	}
	if (bDelete)
	{
		MemManagerDelete();
	}

	return new_ref_count;
}

int MR::CMRRef::ReleaseNoDelete() const
{
	unsigned int new_ref_count;
	{
#if MR_USE_MULTITHREAD
		std::lock_guard<std::mutex> lck(m_RefMutex);
#endif
		assert(m_nRefCount > 0);
		if (m_nRefCount <= 0)
		{
			return 0;
		}
		new_ref_count = --m_nRefCount;
	}
	return new_ref_count;
}

int MR::CMRRef::ReferenceCount() const
{
	return m_nRefCount;
}


void MR::CMRRef::MemManagerDelete() const
{
	GetMemManager()->RequestDelete(this);
}

#ifdef NOT_FORCE_USE_THREAD_SAFE_IN_OBJECT
MR::CMRRef::CMRRef(bool bThreadSafeRefUnref) :
	m_RefMutex(),
	m_nRefCount(0),
	m_pSubsciption(nullptr)
{
	if (bThreadSafeRefUnref)
	{
		m_RefMutex = std::make_shared<std::mutex>();

	}
}

MR::CMRRef::CMRRef(const CMRRef& obj) :
#if MR_USE_MULTITHREAD
	m_RefMutex(),
#endif
	m_nRefCount(0)
{
	//TODO: MR::CMRRef::CMRRef is not implemented

}

void MR::CMRRef::SetThreadSafeRefUnref(bool bThreadSafe)
{
	if (bThreadSafe)
	{
		if (!m_RefMutex)
		{
			m_RefMutex = std::make_shared<std::mutex>();

		}
	}
	else
	{
		if (m_RefMutex)
		{
			m_RefMutex.reset();
		}
	}
}

bool MR::CMRRef::GetThreadSafeRefUnref() const
{
	//TODO: MR::CMRRef::GetThreadSafeRefUnref is not implemented
	return ((bool)m_RefMutex);
}

void MR::CMRRef::SetThreadSafeReferenceCounting(bool bEnableThreadSafeReferenceCounting)
{
	s_bUseThreadSafeReferenceCounting = bEnableThreadSafeReferenceCounting;
}

bool MR::CMRRef::GetThreadSafeReferenceCounting()
{
	return s_bUseThreadSafeReferenceCounting;
}
#endif // NOT_FORCE_USE_THREAD_SAFE_IN_OBJECT

