#ifndef CMRStateGraphNode_h__
#define CMRStateGraphNode_h__

#include "CMRRef.h"
#include "SmartPtr.h"
#include "CMRRenderLeaf.h"
#include "CMRShader.h"
namespace MR
{
	class CMRStateGraphNode : public CMRRef
	{
	public:
		typedef map<const CMRShader*, SmartPtr<CMRStateGraphNode> > ChildrenList ;
		typedef vector<SmartPtr<CMRRenderLeaf> > LeafList;
	public:
		CMRStateGraphNode();
		CMRStateGraphNode(CMRStateGraphNode* pParent, const CMRShader* pShader);

		CMRStateGraphNode* AddShader(const CMRShader* pShader);

		CMRShader* GetShader() const;

		void AddReaderLeaf(CMRRenderLeaf* leaf);

		unsigned int GetNumRenderLeaf() const;

		CMRRenderLeaf* GetRenderLeaf(unsigned int index) const;

		CMRStateGraphNode* GetParent() const;

		ChildrenList& GetStateGraphChildren();

		LeafList& GetRenderLeafList();

		unsigned int GetNumChildren() const;
	protected:
		CMRStateGraphNode* m_pParent;
		ChildrenList m_children;
		LeafList m_leaves;
		SmartPtr<const CMRShader> m_spShader;
	}; 
}
#endif // CMRStateGraphNode_h__
