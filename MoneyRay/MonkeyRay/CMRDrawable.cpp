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

void MR::CMRDrawable::Draw(CMRProgram* program)
{
	DrawImplemention(program);
}

void MR::CMRDrawable::DrawImplemention(CMRProgram* program)
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

void MR::CMRDrawable::AddUniform(CMRUniformRef* pUniform)
{
	m_uniformList.push_back(pUniform);
}

void MR::CMRDrawable::Update()
{
	for (auto& x : m_uniformList)
	{
		if (x->GetUniformName() == "iGlobalTime")
		{
			CMRUniform1fv* pUniform = dynamic_cast<CMRUniform1fv*>(x.Get());
			if (pUniform != NULL)
			{
				GLfloat data[1] = { 0 };
				data[0] = CMRTimer::Instance()->TimeS();
				pUniform->SetData(data);
			}
		}
	}
}

MR::CMRDrawable::~CMRDrawable()
{

}

void MR::CMRDrawable::_ApplyUniform(CMRProgram* program)
{
	for (auto& x: m_uniformList)
	{
		program->Accept(*(x.Get()));
	}
}

void MR::CMRDrawable::Ascend(CMRNodeVisitor& nv)
{
}

void MR::CMRDrawable::Traverse(CMRNodeVisitor& nv)
{
	Accept(nv);
}
