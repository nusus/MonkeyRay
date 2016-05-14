#ifndef CMRNode_h__
#define CMRNode_h__

#include "CMRObject.h"
#include "CMRCallback.h"
#include "vmath.h"
#include "SmartPtr.h"
namespace MR
{
	class CMRNodeVisitor;
	class CMRDrawable;
	class CMRCamera;

	class CMRNode :public CMRObject
	{
	public:
		typedef vector<SmartPtr<CMRNode>> NodeList;
		typedef vector<CMRNode*> ParentList;


	public:
		CMRNode();


	public:
		virtual CMRNode* AsNode() override;
		virtual const CMRNode* AsNode() const override;


	public:
		const ParentList& GetParents() const;
		ParentList& GetParents();
		CMRNode* GetParent(unsigned int index);
		const CMRNode* GetParent(unsigned int index) const;
		unsigned int GetNumParents() const;

		void SetUpdateCallback(CMRCallback* pUC);
		template <typename T>
		void SetUpdateCallback(const SmartPtr<T>& spUC);
		CMRCallback* GetUpdateCallback();
		const CMRCallback* GetUpdateCallback() const;
		void AddUpdateCallback(CMRCallback* pc);
		template<typename T>
		void AddUpdateCallback(const SmartPtr<T>& spUC);
		void RemoveUpdateCallback(CMRCallback* pUC);
		template<typename T>
		void RemoveUpdateCallback(const SmartPtr<CMRCallback>& pCallback);

		void SetEventCallback(CMRCallback* cb);	
		template<typename T>
		void SetEventCallback(const SmartPtr<T>& cb);
		CMRCallback* GetEventCallback();		
		const CMRCallback* GetEventCallback() const;
		void AddEventCallback(CMRCallback* cb);
		template<typename T>
		void AddEventCallback(const SmartPtr<T>& cb);
		void RemoveEventCallback(CMRCallback* cb);	
		template<typename T>
		void RemoveEventCallback(const SmartPtr<T>& cb);

		void AddTransform(const vmath::mat4& matrix);

		vmath::mat4 GetTransform() const;

		virtual void Accept(CMRNodeVisitor& nv);

		virtual void Ascend(CMRNodeVisitor& nv);

		virtual void Traverse(CMRNodeVisitor& nv);

	public:
		virtual bool AddChild(CMRNode* child);
		template<typename T> bool AddChild(const SmartPtr<T>& child);

		virtual bool InsertChild(unsigned int index, CMRNode* child);
		template<typename T> bool InsertChild(unsigned int index, const SmartPtr<T>& child);

		bool RemoveChild(unsigned int pos, unsigned int numChildrenToRemove = 1);
		virtual bool RemoveChildren(unsigned int pos, unsigned int numChildrenToRemove);

		virtual bool ReplaceChild(CMRNode* oriChild, CMRNode* newChild);
		template<typename T, typename R> bool ReplaceChild(const SmartPtr<T>& oriChild, const SmartPtr<R>& newChild);

		virtual unsigned int GetNumChildren() const;

		virtual bool SetChild(unsigned int index, CMRNode* newChild);

		CMRNode* GetChild(unsigned int index);
		const CMRNode* GetChild(unsigned int index) const;

		bool ContainsNode(const CMRNode* pNode) const;

		template <typename T>
		bool ContainsNode(const SmartPtr<T>& spNode);

		unsigned int GetChildIndex(CMRNode* pNode) const;


	protected:
		CMRNode(const CMRNode& node);
		virtual ~CMRNode();


	protected:
		void AddParent(CMRNode* parent);
		void RemoveParent(CMRNode* parent);


	protected:
		ParentList m_parents;
		NodeList m_children;
		SmartPtr<CMRCallback> m_spUpdateCallback;
		SmartPtr<CMRCallback> m_spEventCallback;
		vmath::mat4 m_matTransform;
	};

}
#endif // CMRNode_h__
