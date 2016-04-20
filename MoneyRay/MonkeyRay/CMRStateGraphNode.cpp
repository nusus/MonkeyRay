#include "CMRStateGraphNode.h"

using namespace MR;

MR::CMRStateGraphNode::CMRStateGraphNode(CMRStateGraphNode* pParent, const CMRShader* pShader) :
	m_pParent(pParent),
	m_children(),
	m_leaves(),
	m_spShader(pShader)
{

}

MR::CMRStateGraphNode::CMRStateGraphNode() :m_pParent(nullptr),
m_children(),
m_leaves(),
m_spShader(nullptr)
{

}

CMRStateGraphNode* MR::CMRStateGraphNode::AddShader(const CMRShader* pShader)
{
	ChildrenList::iterator itr = m_children.find(pShader);
	if (itr != m_children.end())
	{
		return (*itr).second.Get();
	}
	CMRStateGraphNode* node = new CMRStateGraphNode(this, pShader);
	m_children[pShader] = node;
	return node;
}

CMRShader* MR::CMRStateGraphNode::GetShader() const
{
	return const_cast<CMRShader*>(m_spShader.Get());
}

void MR::CMRStateGraphNode::AddReaderLeaf(CMRRenderLeaf* leaf)
{
	if (leaf)
	{
		m_leaves.push_back(leaf);
	}
}

unsigned int MR::CMRStateGraphNode::GetNumRenderLeaf() const
{
	return m_leaves.size();
}

CMRRenderLeaf* MR::CMRStateGraphNode::GetRenderLeaf(unsigned int index) const
{
	if (index > GetNumRenderLeaf())
	{
		return nullptr;
	}
	return m_leaves[index].Get();
}

CMRStateGraphNode* MR::CMRStateGraphNode::GetParent() const
{
	return m_pParent;
}

CMRStateGraphNode::ChildrenList& MR::CMRStateGraphNode::GetStateGraphChildren()
{
	return m_children;
}

CMRStateGraphNode::LeafList& MR::CMRStateGraphNode::GetRenderLeafList()
{
	return m_leaves;
}

unsigned int MR::CMRStateGraphNode::GetNumChildren() const
{
	return m_children.size();
}
