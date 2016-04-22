#include "CMRDrawable.h"

using namespace  MR;



MR::CMRDrawable& MR::CMRDrawable::operator=(const CMRDrawable& rhs)
{
	if (&rhs == this)
	{
		return *this;
	}
	m_mvpwMatrix = rhs.m_mvpwMatrix;
	m_shaderSet = rhs.m_shaderSet;
	return *this;
}

MR::CMRDrawable::CMRDrawable(const CMRDrawable& rhs) :m_mvpwMatrix(rhs.m_mvpwMatrix),
m_shaderSet(rhs.m_shaderSet)
{

}

MR::CMRDrawable::CMRDrawable()
{

}

void MR::CMRDrawable::Draw()
{
	DrawImplemention();
}

void MR::CMRDrawable::DrawImplemention()
{

}

void MR::CMRDrawable::SetMVPWMatrix(const vmath::mat4& matrix)
{
	m_mvpwMatrix = matrix;
}

vmath::mat4 MR::CMRDrawable::GetMVPWMatrix() const
{
	return m_mvpwMatrix;
}

CMRShader::ShaderSet MR::CMRDrawable::GetShaderSet() const
{
	return m_shaderSet;
}

void MR::CMRDrawable::AddShader(CMRShader* pShader)
{
	m_shaderSet.insert(pShader);
}

MR::CMRDrawable::~CMRDrawable()
{

}
