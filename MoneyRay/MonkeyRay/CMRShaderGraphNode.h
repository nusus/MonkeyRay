#ifndef CMRShaderGraphNode_h__
#define CMRShaderGraphNode_h__

#include "CMRPrerequisites.h"
#include "CMRRef.h"
#include "SmartPtr.h"
#include "CMRGeode.h"
#include "CMRRenderLeaf.h"
#include "CMRShader.h"
namespace MR
{
	class CMRShaderGraphNode : public CMRRef
	{
	public:
		typedef map<const CMRShader*, SmartPtr<CMRShaderGraphNode> > ChildrenList ;
		typedef list<SmartPtr<CMRRenderLeaf> > LeafList;
	public:
		CMRShaderGraphNode()
			:m_pParent(nullptr),
			m_children(),
			m_leaves(),
			m_spShader(nullptr)
		{

		}
		CMRShaderGraphNode(CMRShaderGraphNode* pParent,const CMRShader* pShader) :
			m_pParent(pParent),
			m_children(),
			m_leaves(),
			m_spShader(pShader)
		{

		}

		CMRShaderGraphNode* AddChild(const CMRShader* pShader)
		{
			ChildrenList::iterator itr = m_children.find(pShader);
			if (itr != m_children.end())
			{
				return (*itr).second.Get();
			}
			CMRShaderGraphNode* node = new CMRShaderGraphNode(this, pShader);
			m_children[pShader] = node;
			return node;
		}

		CMRRenderLeaf* AddReaderLeaf(const CMRRenderLeaf* leaf)
		{
			if (leaf)
			{
				m_leaves.push_back(leaf);
			}
		}
	protected:
		CMRShaderGraphNode* m_pParent;
		ChildrenList m_children;
		LeafList m_leaves;
		SmartPtr<const CMRShader> m_spShader;
	}; 
}
#endif // CMRShaderGraphNode_h__
