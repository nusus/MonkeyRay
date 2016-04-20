#include "CMRRenderStage.h"
#include "CMRStateGraph.h"

using namespace MR;

MR::CMRRenderStage::CMRRenderStage() :CMRRenderBin(),
m_bInitialized(false)
{

}

void MR::CMRRenderStage::Reset()
{
	m_renderLeafList.clear();
	m_renderBinChildren.clear();
	m_bInitialized = false;
}

void MR::CMRRenderStage::Draw() const
{
	for (int i = 0; i < GetNumRenderBinChildren(); ++i)
	{
		CMRRenderBin* pBin = GetRenderBinChild(i);
		pBin->Draw();
	}
}

void MR::CMRRenderStage::Init(CMRStateGraph* pStateGraph)
{
	if (pStateGraph->GetNumChildren() <= 0)
	{
		return;
	}

	CMRStateGraph::ChildrenList& children = pStateGraph->GetStateGraphChildren();
	for (auto& x : children)
	{
		m_shaderStack.push_back(x.first);
		Apply(*(x.second));
		m_shaderStack.pop_back();
	}

	m_bInitialized = false;
}

void MR::CMRRenderStage::Apply(CMRStateGraphNode& node)
{
	if (node.GetNumRenderLeaf() > 0)
	{
		SmartPtr<CMRRenderBin> pRenderBin = new CMRRenderBin;
		for (auto shader : m_shaderStack)
		{
			pRenderBin->AddShader((const_cast<CMRShader*>(shader)));
		}
		CMRStateGraphNode::LeafList& leafList = node.GetRenderLeafList();
		for (auto& leaf : leafList)
		{
			pRenderBin->AddRenderLeaf(leaf.Get());
		}
	}
	if (node.GetNumChildren() <= 0)
	{
		return;
	}
	CMRStateGraph::ChildrenList& children = node.GetStateGraphChildren();
	for (auto& x : children)
	{
		m_shaderStack.push_back(x.first);
		Apply(*(x.second));
		m_shaderStack.pop_back();
	}
}

bool MR::CMRRenderStage::IsInit() const
{
	return m_bInitialized;
}
