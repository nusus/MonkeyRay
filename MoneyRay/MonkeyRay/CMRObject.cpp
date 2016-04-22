#include "CMRObject.h"

using namespace MR;

CMRObject& MR::CMRObject::operator=(const CMRObject&)
{
	return *this;
}

void MR::CMRObject::SetName(const char* pszName)
{
	if (pszName == nullptr)
	{
		SetName(string());
	}
	else
	{
		SetName(string(pszName));
	}
}

void MR::CMRObject::SetName(const string& name)
{
	m_strName = name;
}

const string& MR::CMRObject::GetName() const
{
	return m_strName;
}

MR::CMRObject::~CMRObject()
{

}
