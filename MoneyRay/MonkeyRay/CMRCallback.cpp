#include "CMRCallback.h"
#include "SmartPtr.h"

using namespace MR;

MR::CMRCallback::CMRCallback()
{

}

bool MR::CMRCallback::Run(CMRObject* pObject)
{
	RunImpl(pObject);
	return Traverse(pObject);
}

void MR::CMRCallback::RunImpl(CMRObject* pObject)
{

}

bool MR::CMRCallback::Traverse(CMRObject* pObject)
{
	if (m_spNestedCallback.Valid())
	{
		return m_spNestedCallback->Run(pObject);
	}
	return false;
}

void MR::CMRCallback::AddNestedCallback(CMRCallback* pc)
{
	if (pc)
	{
		if (m_spNestedCallback.Valid())
		{
			m_spNestedCallback->AddNestedCallback(pc);
		}
		else
		{
			m_spNestedCallback = pc;
		}
	}
}

void MR::CMRCallback::RemoveNestedCallback(CMRCallback* pUC)
{
	if (pUC)
	{
		if (m_spNestedCallback == pUC)
		{
			SmartPtr<CMRCallback> new_nested_callback = m_spNestedCallback->GetNestedCallback();
			m_spNestedCallback->SetNestedCallback(nullptr);
			m_spNestedCallback = new_nested_callback;
		}
		else
		{
			if (m_spNestedCallback.Valid())
			{
				m_spNestedCallback->RemoveNestedCallback(pUC);
			}
		}
	}
}

void MR::CMRCallback::SetNestedCallback(CMRCallback* param1)
{
	m_spNestedCallback = param1;
}

const CMRCallback* MR::CMRCallback::GetNestedCallback() const
{
	return m_spNestedCallback.Get();
}

CMRCallback* MR::CMRCallback::GetNestedCallback()
{
	return m_spNestedCallback.Get();
}

MR::CMRCallback::~CMRCallback()
{

}
