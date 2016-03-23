#include "CMRObserver.h"

using namespace MR;

MR::CMRSubsciber::CMRSubsciber()
{

}

MR::CMRSubsciber::~CMRSubsciber()
{

}

MR::CMRSubsciption::CMRSubsciption(const CMRRef* ptr):
	m_pPublisher(const_cast<CMRRef*>(ptr))
{

}

void MR::CMRSubsciption::AddSubscriber(CMRSubsciber* obj)
{
#if MR_USE_MULTITHREAD
	std::lock_guard<std::mutex> lck(m_mutex);
#endif
	m_Subscibers.insert(obj);
}

void MR::CMRSubsciption::RemoveSubscriber(CMRSubsciber* obj)
{
#if MR_USE_MULTITHREAD
	std::lock_guard<std::mutex> lck(m_mutex);
#endif
	m_Subscibers.erase(obj);
}

void MR::CMRSubsciption::SignalObjectDeleted(void* ptr)
{
#if MR_USE_MULTITHREAD
	std::lock_guard<std::mutex> lck(m_mutex);
#endif
	for (auto itr = m_Subscibers.begin(); itr != m_Subscibers.end(); ++itr)
	{
		(*itr)->SubsciberDeleted(ptr);
	}
	m_Subscibers.clear();
	m_pPublisher = nullptr;
}

MR::CMRSubsciption::~CMRSubsciption()
{

}

CMRRef* MR::CMRSubsciption::AddRefLock()
{
#if MR_USE_MULTITHREAD
	std::lock_guard<std::mutex> lck(m_mutex);
#endif
	
	if (!m_pPublisher)
	{
		return nullptr;
	}

	int refCount = m_pPublisher->Retain();
	if (refCount == 1)
	{
		m_pPublisher->ReleaseNoDelete();
		return nullptr;
	}

	return m_pPublisher;
}
