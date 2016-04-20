#include "CMRDrawable.h"

using namespace  MR;



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
