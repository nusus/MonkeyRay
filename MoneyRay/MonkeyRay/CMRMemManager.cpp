#include "CMRMemManager.h"

using namespace MR;

MR::CMRMemManager::CMRMemManager(unsigned int nNumFramesToRetainObjects /*= 0*/):
	m_nNumberFramesToRetainObjects(nNumFramesToRetainObjects),
	m_nCurrentFrameNumber(0)
{

}

CMRMemManager& MR::CMRMemManager::operator=(const CMRMemManager&)
{
	return *this;
}

MR::CMRMemManager::~CMRMemManager()
{

}

void MR::CMRMemManager::SetNumberFramesToRetainObjects(unsigned int nNumFramesToRetainObjects)
{
	m_nNumberFramesToRetainObjects = nNumFramesToRetainObjects;
}

unsigned int MR::CMRMemManager::GetNumberFramesToRetainObjects() const
{
	return m_nNumberFramesToRetainObjects;
}

void MR::CMRMemManager::SetCurrentFrameNumber(unsigned int nCurrentFrame)
{
	m_nCurrentFrameNumber = nCurrentFrame;
}

unsigned int MR::CMRMemManager::GetCurrentFrameNumber() const
{
	return m_nCurrentFrameNumber;
}

void MR::CMRMemManager::DeleteAux(const CMRRef* obj)
{
	delete obj;
}

void MR::CMRMemManager::Flush()
{
	typedef MR::list<const CMRRef*> ObjectToDeleteList;
	ObjectToDeleteList object_to_delete_list;

	{
#if MR_USE_MULTITHREAD
		std::lock_guard<std::mutex> lck(m_mutex);
#endif
		unsigned int nFrameNumberToClearTo = m_nCurrentFrameNumber - m_nNumberFramesToRetainObjects;

		for (auto itr = m_ObejectsToDelete.begin(); itr != m_ObejectsToDelete.end(); ++itr)
		{
			if ((*itr).first > nFrameNumberToClearTo)
			{
				break;
			}

			object_to_delete_list.push_back((*itr).second);
			(*itr).second = nullptr;
		}

		object_to_delete_list.clear();
	}

	for (auto itr = object_to_delete_list.begin(); itr != object_to_delete_list.end(); ++itr)
	{
		DeleteAux((*itr));
	}
}

void MR::CMRMemManager::FlushAll()
{
	unsigned int temp = m_nNumberFramesToRetainObjects;
	m_nNumberFramesToRetainObjects = 0;

	typedef MR::list<const CMRRef*> ObjectToDeleteList;
	ObjectToDeleteList object_to_delete_list;

	{
		#if MR_USE_MULTITHREAD
std::lock_guard<std::mutex> lck(m_mutex);
#endif

		for (auto itr = m_ObejectsToDelete.begin(); itr != m_ObejectsToDelete.end(); ++itr)
		{
			object_to_delete_list.push_back((*itr).second);
			(*itr).second = nullptr;
		}

		object_to_delete_list.clear();
	}

	for (auto itr = object_to_delete_list.begin(); itr != object_to_delete_list.end(); ++itr)
	{
		DeleteAux((*itr));
	}

	m_nNumberFramesToRetainObjects = temp;
}

void MR::CMRMemManager::RequestDelete(const CMRRef* obj)
{
	if (m_nNumberFramesToRetainObjects == 0)
	{
		DeleteAux((obj));
	}
	else
	{
		#if MR_USE_MULTITHREAD
std::lock_guard<std::mutex> lck(m_mutex);
#endif
		m_ObejectsToDelete.push_back(FrameNumberObjectPair(m_nCurrentFrameNumber, obj));
	}
}

MR::CMRMemManager::CMRMemManager(const CMRMemManager&) :
	m_nNumberFramesToRetainObjects(0),
	m_nCurrentFrameNumber(0)
{

}

