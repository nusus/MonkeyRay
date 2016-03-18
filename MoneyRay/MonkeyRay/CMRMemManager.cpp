#include "CMRMemManager.h"
#include "CMRContainerConfig.h"
MR::CMRMemManager::CMRMemManager(unsigned int nNumFramesToRetainObjects /*= 0*/):
	m_nNumberFramesToRetainObjects(nNumFramesToRetainObjects),
	m_nCurrentFrameNumber(0)
{

}

MR::CMRMemManager::~CMRMemManager()
{

}

void MR::CMRMemManager::Flush()
{
	typedef MR::list<const CMRRef*> ObjectToDeleteList;
	ObjectToDeleteList object_to_delete_list;

	{
		std::lock_guard<std::mutex> lck(m_mutex);
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
		std::lock_guard<std::mutex> lck(m_mutex);

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
		std::lock_guard<std::mutex> lck(m_mutex);
		m_ObejectsToDelete.push_back(FrameNumberObjectPair(m_nCurrentFrameNumber, obj));
	}
}

