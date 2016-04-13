#include "CMRUserDataContainer.h"

using namespace MR;

CMRUserDataContainer::CMRUserDataContainer() : CMRObject() {}

MR::CMRUserDataContainer::CMRUserDataContainer(const CMRUserDataContainer& obj, const CMRCopyPolicy& policy):
	CMRObject(obj, policy)
{

}

CMRObject* MR::CMRUserDataContainer::GetUserObject(const string& strName, unsigned int nStartPosition /*= 0*/)
{
	return GetUserObject(GetUserObjectIndex(strName, nStartPosition));
}

const CMRObject* MR::CMRUserDataContainer::GetUserObject(const string& strName, unsigned int nStartPosition /*= 0*/) const
{
	return GetUserObject(GetUserObjectIndex(strName, nStartPosition));
}

MR::CMRDefaultUserDataContainer::CMRDefaultUserDataContainer()
{

}

MR::CMRDefaultUserDataContainer::CMRDefaultUserDataContainer(const CMRDefaultUserDataContainer& obj, const CMRCopyPolicy& policy) :
	CMRUserDataContainer(obj, policy)
{
	m_userData = obj.m_userData;
	m_descriptionList = obj.m_descriptionList;
	m_objectList.clear();
	for (
		auto itr = obj.m_objectList.begin(); 
		itr != obj.m_objectList.end();
		++itr
	)
	{
		m_objectList.push_back(policy.Copy((*itr).Get()));
	}
}

void MR::CMRDefaultUserDataContainer::SetUserData(CMRRef* obj)
{
	m_userData = obj;
}


CMRRef* MR::CMRDefaultUserDataContainer::GetUserData()
{
	return m_userData.Get();
}

unsigned int MR::CMRDefaultUserDataContainer::AddUserObject(CMRObject* obj)
{
	unsigned int index = GetUserObjectIndex(obj);
	if (index < m_objectList.size())
	{
		return index;
	}

	unsigned int ret= m_objectList.size();
	m_objectList.push_back(obj);
	return ret;
}

void MR::CMRDefaultUserDataContainer::SetUserObject(unsigned int index, CMRObject* obj)
{
	if (index < m_objectList.size())
	{
		m_objectList[index] = obj;
	}
}

void MR::CMRDefaultUserDataContainer::RemoveUserObject(unsigned int index)
{
	if (index < m_objectList.size())
	{
		m_objectList.erase( m_objectList.begin() + index);
	}
}

CMRObject* MR::CMRDefaultUserDataContainer::GetUserObject(unsigned int index)
{
	if (index < m_objectList.size())
	{
		return m_objectList[index].Get();
	}
	return nullptr;
}

unsigned int MR::CMRDefaultUserDataContainer::GetNumUserObjects() const
{
	return m_objectList.size();
}

unsigned int MR::CMRDefaultUserDataContainer::GetUserObjectIndex(const CMRObject* obj, unsigned int nStartPosition /*= 0*/) const
{
	for (int i = nStartPosition; i < m_objectList.size(); ++i)
	{
		if (m_objectList[i].Get() == obj)
		{
			return i;
		}
	}
	return m_objectList.size();
}

void MR::CMRDefaultUserDataContainer::SetDescriptions(const DescriptionList& dl)
{
	m_descriptionList = dl;
}

CMRDefaultUserDataContainer::DescriptionList & MR::CMRDefaultUserDataContainer::GetDescriptions()
{
	return m_descriptionList;
}


const CMRDefaultUserDataContainer::DescriptionList& MR::CMRDefaultUserDataContainer::GetDescriptions() const
{
	return m_descriptionList;
}

void MR::CMRDefaultUserDataContainer::AddDescription(const string& strName)
{
	m_descriptionList.push_back(strName);
}

unsigned int MR::CMRDefaultUserDataContainer::GetNumDescriptions() const
{
	m_descriptionList.size();
}

unsigned int MR::CMRDefaultUserDataContainer::GetUserObjectIndex(const string& strName, unsigned int nStartPosition /*= 0*/) const
{
	for (int i = nStartPosition; i < m_objectList.size(); ++i)
	{
		CMRObject* obj = m_objectList[i].Get();
		if (obj && obj->GetName() == strName)
		{
			return i;
		}
	}
	return m_objectList.size();
}

const CMRObject* MR::CMRDefaultUserDataContainer::GetUserObject(unsigned int index) const
{
	if (index < m_objectList.size())
	{
		return m_objectList[index].Get();
	}
	return nullptr;
}

const CMRRef* MR::CMRDefaultUserDataContainer::GetUserData() const
{
	return m_userData.Get();
}
