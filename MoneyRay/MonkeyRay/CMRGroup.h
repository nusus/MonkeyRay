#ifndef CMRGroup_h__
#define CMRGroup_h__
#include "CMRNode.h"
#include "CMRMacroUtil.h"
namespace MR
{
	typedef vector<SmartPtr<CMRNode> > NodeList;

	class CMRGroup : public CMRNode
	{
	public:
		CMRGroup();

		CMRGroup(const CMRGroup&, const CMRCopyPolicy& policy = CMRCopyPolicy::SHALLOW_COPY);


		META_NODE(CMRGroup);

	public:
		virtual CMRGroup* AsGroup() { return this; }
		virtual const CMRGroup* AsGroup() const { return this; }

		virtual void Traverse(CMRNodeVisitor& nv);

		virtual bool AddChild(CMRNode* child);
		template<typename T> bool AddChild(const SmartPtr<T>& child) { return AddChild(child.Get()); }

		virtual bool InsertChild(unsigned int index, CMRNode* child);
		template<typename T> bool InsertChild(unsigned int index, const SmartPtr<T>& child) { return InsertChild(index, child.Get()); }

		inline bool RemoveChild(unsigned int pos, unsigned int numChildrenToRemove = 1)
		{
			if (pos < m_children.size())
			{
				return RemoveChildren(pos, numChildrenToRemove);
			}
			return false;
		}

		virtual bool RemoveChildren(unsigned int pos, unsigned int numChildrenToRemove);

		virtual bool ReplaceChild(CMRNode* oriChild, CMRNode* newChild);

		template<typename T, typename R> bool ReplaceChild(const SmartPtr<T>& oriChild, const SmartPtr<R>& newChild) { return ReplaceChild(oriChild.Get(), newChild.Get()); }

		virtual unsigned int GetNumChildren() const;

		virtual bool SetChild(unsigned int index, CMRNode* newChild);

		inline CMRNode* GetChild(unsigned int index) { return m_children[index].Get(); }

		inline const CMRNode* GetChild(unsigned int index) const { return m_children[index].Get(); }

		inline bool ContainsNode(const CMRNode* pNode) const
		{
			for (
				auto itr = m_children.begin();
				itr != m_children.end();
				++itr
			)
			{
				if ( (*itr).Get() == pNode )
				{
					return true;
				}
			}
			return false;
		}

		template <typename T>
		bool ContainsNode(const SmartPtr<T>& spNode)
		{
			return ContainsNode(spNode.Get());
		}

		inline unsigned int GetChildIndex(CMRNode* pNode) const
		{
			for (int i = 0; i < m_children.size(); ++i )
			{
				if (m_children[i].Get() == pNode )
				{
					return i;
				}
			}
			return static_cast<unsigned int> (m_children.size());
		}

		virtual void ResizeGLObjectBuffers(unsigned int maxSize) override;

		virtual void ReleaseGLObjects(CMRState* pState = 0) const override;

		virtual CMRBoundingSphere ComputeBound()() const override;
	protected:
		virtual ~CMRGroup();

		virtual void ChildRemoved(unsigned int pos, unsigned int numChildrenToRemove) {}
		virtual void ChildInserted(unsigned int pos) {}
	protected:

		NodeList m_children;
	};
}
#endif // CMRGroup_h__
