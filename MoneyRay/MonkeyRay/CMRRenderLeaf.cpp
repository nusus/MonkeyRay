#include "CMRRenderLeaf.h"
#include "CMRProgram.h"

using namespace MR;

MR::CMRRenderLeaf::CMRRenderLeaf(const vmath::mat4& matrix, CMRDrawable* pDrawable) :m_mvpwMatrix(matrix),
m_spDrawable(pDrawable)
{

}

void MR::CMRRenderLeaf::SetMVPWMatrix(const vmath::mat4& matrix)
{
	m_mvpwMatrix = matrix;
}

vmath::mat4 MR::CMRRenderLeaf::GetMVPWMatrix() const
{
	return m_mvpwMatrix;
}

void MR::CMRRenderLeaf::SetDrawable(CMRDrawable* pDrawable)
{
	m_spDrawable = pDrawable;
}

CMRDrawable* MR::CMRRenderLeaf::GetDrawable() const
{
	return m_spDrawable.Get();
}

void MR::CMRRenderLeaf::Draw(CMRProgram* program)
{
	m_spDrawable->Draw(program);
}
