#include "CMRRef.h"
#include <assert.h>
#include "CMRMemManager.h"
#include "CMRObserver.h"

std::mutex* MR::CMRRef::GetGlobalReferenceMutex()
{
	static std::shared_ptr<std::mutex> s_GlobalRefMutex = std::make_shared<std::mutex>();
	return s_GlobalRefMutex.get();
}

MR::CMRMemManager* MR::CMRRef::GetMemManager()
{

	static std::shared_ptr<MR::CMRMemManager> s_MemManager = std::make_shared<MR::CMRMemManager>(1);
	return s_MemManager.get();
}


struct SMRInit
{
	SMRInit()
	{
		MR::CMRRef::GetGlobalReferenceMutex();
		MR::CMRRef::GetMemManager();
	}
};

static SMRInit s_initGlobalMutex;
static bool s_bUseThreadSafeReferenceCounting = true;


MR::CMRRef::CMRRef():
	m_RefMutex(),
	m_nRefCount(0),
	m_pSubsciption(nullptr)
{

}



MR::CMRRef::~CMRRef()
{
	SignalObserversToDelete();
	if (m_pSubsciption)
	{
		static_cast<CMRSubsciption*>(m_pSubsciption)->Release();
	}

}


int MR::CMRRef::Retain() const
{

	std::lock_guard<std::mutex> lck(m_RefMutex);
	return ++m_nRefCount;
}

int MR::CMRRef::Release() const
{
	unsigned int new_ref_count;
	bool bDelete = false;
	{
		std::lock_guard<std::mutex> lck(m_RefMutex);
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

MR::CMRSubsciption* MR::CMRRef::GetOrCreateSubscription() const
{
	{
		std::lock_guard<std::mutex> lck(m_RefMutex);
		if (!m_pSubsciption)
		{
			m_pSubsciption = new CMRSubsciption(this);
			static_cast<CMRSubsciption*>(m_pSubsciption)->Retain();
		}
		return static_cast<CMRSubsciption*>(m_pSubsciption);
	}
}

int MR::CMRRef::ReleaseNoDelete() const
{
	unsigned int new_ref_count;
	{
		std::lock_guard<std::mutex> lck(m_RefMutex);
		assert(m_nRefCount > 0);
		if (m_nRefCount <= 0)
		{
			return 0;
		}
		new_ref_count = --m_nRefCount;
	}
	return new_ref_count;
}

void MR::CMRRef::AddSubcriber(CMRSubsciber* subsciber) const
{
	GetOrCreateSubscription()->AddSubscriber(subsciber);
}

void MR::CMRRef::RemoveSubsciber(CMRSubsciber* subscriber) const
{
	GetOrCreateSubscription()->RemoveSubscriber(subscriber);
}



void MR::CMRRef::SignalObserversToDelete() const
{
	if (m_pSubsciption)
	{
		static_cast<CMRSubsciption*>(m_pSubsciption)->SignalObjectDeleted(const_cast<CMRRef*>(this));
	}
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
void MR::CMRRef::SetThreadSafeReferenceCounting(bool bEnableThreadSafeReferenceCounting)
{
	s_bUseThreadSafeReferenceCounting = bEnableThreadSafeReferenceCounting;
}

bool MR::CMRRef::GetThreadSafeReferenceCounting()
{
	return s_bUseThreadSafeReferenceCounting;
}
#endif // NOT_FORCE_USE_THREAD_SAFE_IN_OBJECT

