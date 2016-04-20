#include "CMRRenderBin.h"
#include "CMRProgram.h"
#include "CMRUniform.h"
#include "CMRRenderLeaf.h"

using namespace MR;

MR::CMRRenderBin::CMRRenderBin()
{
	m_spProgram = new CMRProgram;
}

void MR::CMRRenderBin::AddRenderBin(CMRRenderBin* pBin)
{
	m_renderBinChildren.push_back(pBin);
}

unsigned int MR::CMRRenderBin::GetNumRenderBinChildren() const
{
	return m_renderBinChildren.size();
}

CMRRenderBin* MR::CMRRenderBin::GetRenderBinChild(unsigned int index) const
{
	if (index > GetNumRenderBinChildren())
	{
		return nullptr;
	}
	return m_renderBinChildren[index].Get();
}

void MR::CMRRenderBin::AddRenderLeaf(CMRRenderLeaf* pLeaf)
{
	m_renderLeafList.push_back(pLeaf);
}

unsigned int MR::CMRRenderBin::GetNumRenderLeaf() const
{
	return m_renderLeafList.size();
}

CMRRenderLeaf* MR::CMRRenderBin::GetRenderLeaf(unsigned int index) const
{
	if (index < GetNumRenderLeaf())
	{
		return m_renderLeafList[index];
	}
	return nullptr;
}

void MR::CMRRenderBin::Draw() const
{
	m_spProgram->InitProgram();
	if (m_spProgram->IsReady())
	{
		m_spProgram->UseProgram();
	}
	else
	{
		return;
	}
	for (auto leaf : m_renderLeafList)
	{
		SmartPtr<CMRUniformRef> pUniform = new CMRUniformMatrix4fv("uni_mvpw_matrix", leaf->GetMVPWMatrix());
		m_spProgram->Accept(*pUniform);
		leaf->Draw();
	}
	m_spProgram->DestroyProgram();
}

void MR::CMRRenderBin::AddShader(CMRShader* pShader)
{
	if (!m_spProgram.Valid())
	{
		m_spProgram = new CMRProgram;
	}
	m_spProgram->AddShader(pShader);
}
