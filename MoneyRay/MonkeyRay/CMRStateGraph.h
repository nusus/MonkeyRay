#ifndef CMRStateGraph_h__
#define CMRStateGraph_h__
#include "CMRStateGraphNode.h"
namespace MR
{
	class CMRStateGraph : public CMRStateGraphNode
	{
	public:
		CMRStateGraph() :
			CMRStateGraphNode(nullptr, nullptr),
			m_bInitialized(false)
		{

		}

		void Init(CMRNode* pNode)
		{
			Apply(*pNode);
			m_bInitialized = true;
		}

		bool IsInit() const 
		{
			return m_bInitialized;
		}

		virtual void Apply(CMRNode& node)
		{
			m_mvpwStack.push_back(node.GetTransform());
			for (auto i = 0; i < node.GetNumChildren(); ++i)
			{
				CMRNode* pNode = node.GetChild(i);
				Apply(*pNode);
			}
			m_mvpwStack.pop_back();

		}

		virtual void Apply(CMRDrawable& node)
		{
			m_mvpwStack.push_back(node.GetTransform());
			CMRStateGraphNode* pStateNode = this->PushShaderSet(node.GetShaderSet());
			SmartPtr<CMRRenderLeaf> pRenderLeaf = new CMRRenderLeaf(_GetMVPWMatrix(), &node);
			pStateNode->AddReaderLeaf(pRenderLeaf.Get());
			m_mvpwStack.pop_back();

		}


		virtual void Apply(CMRCamera& node)
		{
			m_mvpwStack.push_back(node.GetViewport()->ComputeWindowMatrix());
			m_mvpwStack.push_back(node.GetProjectionMatrix());
			m_mvpwStack.push_back(node.GetViewMatrix());
			for (auto i = 0; i < node.GetNumChildren(); ++i)
			{
				CMRNode* pNode = node.GetChild(i);
				Apply(*pNode);
			}
			m_mvpwStack.pop_back();
			m_mvpwStack.pop_back();
			m_mvpwStack.pop_back();
		}

		CMRStateGraphNode* PushShaderSet(const CMRShader::ShaderSet& shaderSet)
		{
			typedef CMRShader::ShaderSet ShaderSet;
			CMRStateGraphNode* pCurrentNode = this;
			for (
				ShaderSet::iterator itr = shaderSet.begin();
				itr != shaderSet.end();
				++ itr)
			{
				if ((*itr).Valid() )
				{
					pCurrentNode = pCurrentNode->AddShader((*itr).Get());
				}
			}
			return pCurrentNode;
		}

		void Reset()
		{
			m_children.clear();
			m_leaves.clear();
			m_mvpwStack.clear();
			m_bInitialized = false;
		}

	protected:
		struct GetMVPWMatrixOp
		{
			vmath::mat4 operator()(const vmath::mat4& lhs, const vmath::mat4& rhs)
			{
				return lhs * rhs;
			}
		};
		vmath::mat4 _GetMVPWMatrix() const
		{
			return std::accumulate(m_mvpwStack.begin(), m_mvpwStack.end(), (vmath::mat4()), GetMVPWMatrixOp());
		}

	protected:
		bool m_bInitialized;

		typedef vector<vmath::mat4>  MatrixStack;
		MatrixStack m_mvpwStack;

	};
}
#endif // CMRStateGraph_h__
