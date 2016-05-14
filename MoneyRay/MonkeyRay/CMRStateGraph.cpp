#include "CMRStateGraph.h"

using namespace MR;

void MR::CMRStateGraph::Init(CMRNode* pNode)
{
	pNode->Traverse(*this);
	m_bInitialized = true;
}

bool MR::CMRStateGraph::IsInit() const
{
	return m_bInitialized;
}

void MR::CMRStateGraph::Apply(CMRCamera& node)
{
	//PushMatrixStack(node.GetViewport()->ComputeWindowMatrix());
	PushMatrixStack(node.GetProjectionMatrix());
	PushMatrixStack(node.GetViewMatrix());
	for (unsigned int i = 0; i < node.GetNumChildren(); ++i)
	{
		CMRNode* pNode = node.GetChild(i);
		pNode->Traverse(*this);
	}
	//PopMatrixStack();
	PopMatrixStack();
	PopMatrixStack();
}

void MR::CMRStateGraph::Apply(CMRNode& node)
{
	PushMatrixStack(node.GetTransform());
	for (unsigned int i = 0; i < node.GetNumChildren(); ++i)
	{
		CMRNode* pNode = node.GetChild(i);
		pNode->Traverse(*this);
	}
	PopMatrixStack();
}

void MR::CMRStateGraph::Apply(CMRDrawable& node)
{
	PushMatrixStack(node.GetTransform());
	CMRStateGraphNode* pStateNode = this->PushShaderSet(node.GetShaderSet());
	SmartPtr<CMRRenderLeaf> pRenderLeaf = new CMRRenderLeaf(_GetMVPWMatrix(), &node);
	pStateNode->AddReaderLeaf(pRenderLeaf.Get());
	PopMatrixStack();
}

CMRStateGraphNode* MR::CMRStateGraph::PushShaderSet(const CMRShader::ShaderSet& shaderSet)
{
	typedef CMRShader::ShaderSet ShaderSet;
	CMRStateGraphNode* pCurrentNode = this;
	for (
		ShaderSet::iterator itr = shaderSet.begin();
		itr != shaderSet.end();
		++itr)
	{
		if ((*itr).Valid())
		{
			pCurrentNode = pCurrentNode->AddShader((*itr).Get());
		}
	}
	return pCurrentNode;
}

void MR::CMRStateGraph::Reset()
{
	m_children.clear();
	m_leaves.clear();
	m_mvpwStack.clear();
	m_bInitialized = false;
}

void MR::CMRStateGraph::PushMatrixStack(const vmath::mat4& matrix)
{
	m_mvpwStack.push_back(matrix);
}

void MR::CMRStateGraph::PopMatrixStack()
{
	m_mvpwStack.pop_back();
}

MR::CMRStateGraph::CMRStateGraph() :
	CMRStateGraphNode(nullptr, nullptr),
	m_bInitialized(false)
{

}

MR::CMRStateGraph::~CMRStateGraph()
{

}

vmath::mat4 MR::CMRStateGraph::_GetMVPWMatrix() const
{
	vmath::mat4 ret = vmath::mat4::identity();
	for (auto& x: m_mvpwStack)
	{
		ret *= x;
	}
	return ret;
}

vmath::mat4 MR::CMRStateGraph::GetMVPWMatrixOp::operator()(const vmath::mat4& lhs, const vmath::mat4& rhs)
{
	return lhs * rhs;
}
