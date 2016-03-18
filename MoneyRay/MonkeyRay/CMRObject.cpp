#include "CMRObject.h"
#include "CMRUserDataContainer.h"

using namespace MR;


MR::CMRObject::CMRObject(const CMRObject& obj, const CMRCopyPolicy& policy /*= CMRCopyPolicy::SHALLOW_COPY*/) :m_strName(obj.m_strName),
m_dataVariance(obj.m_dataVariance),
m_pUserDataContainer(nullptr)
{
	if (obj.m_pUserDataContainer)
	{
		if (policy.GetCopyFlags() & CMRCopyPolicy::DEEP_COPY_USERDATA)
		{
			SetUserDataContainer(MR::Copy(obj.m_pUserDataContainer, policy));
		}
		else
		{
			SetUserDataContainer(obj.m_pUserDataContainer);
		}
	}
}

void MR::CMRObject::SetUserDataContainer(CMRUserDataContainer* udc)
{
	if (udc == m_pUserDataContainer) return;
	if (m_pUserDataContainer)
	{
		m_pUserDataContainer->Release();
	}
	m_pUserDataContainer = udc;
	if (m_pUserDataContainer)
	{
		m_pUserDataContainer->Retain();
	}
}

CMRUserDataContainer* MR::CMRObject::GetOrCreatUserDataContainer()
{
	if (m_pUserDataContainer)
	{
		return m_pUserDataContainer;
	}
	SetUserDataContainer(new CMRDefaultUserDataContainer());
	return m_pUserDataContainer;
}

void MR::CMRObject::SetUserData(CMRRef* obj)
{
	if (GetUserData() == obj)
	{
		return;
	}
	GetOrCreatUserDataContainer()->SetUserData(obj);
}

CMRRef* MR::CMRObject::GetUserData()
{
	return m_pUserDataContainer ? m_pUserDataContainer->GetUserData() : nullptr;
}

const CMRRef* MR::CMRObject::GetUserData() const
{
	return m_pUserDataContainer ? m_pUserDataContainer->GetUserData() : nullptr;
}
