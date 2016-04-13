#ifndef CMRNode_h__
#define CMRNode_h__

#include "CMRBoundingSphere.h"
#include "CMRObject.h"
#include "CMRMatrix.h"
#include "CMRCallback.h"
namespace MR
{
	class CMRTerrain;

	class CMRNodeVisitor;
	class CMRDrawable;
	class CMRGeometry;
	class CMRGroup;
	class CMRTransform;
	class CMRNode;
	class CMRSwitch;
	class CMRGeode;
	class CMRCamera;

	typedef vector<CMRNode*> CMRNodePath;
	typedef vector<CMRNodePath> CMRNodePathList;
	typedef vector<CMRMatrix> CMRMatrixList;

	class CMRNode :public CMRObject
	{
	public:
		typedef unsigned int NodeMask;

		struct ComputeBoundingSphereCallback : public CMRObject 
		{
			ComputeBoundingSphereCallback() {}
			ComputeBoundingSphereCallback(const ComputeBoundingSphereCallback& cbsc, const CMRCopyPolicy& policy) {}
			META_OBJECT(MonkeyRay, ComputeBoundingSphereCallback);
			virtual CMRBoundingSphere ComputeBound(const CMRNode&) const { return CMRBoundingSphere(); }
		};
	public:
		CMRNode();
		CMRNode(const CMRNode& node, const CMRCopyPolicy& policy = CMRCopyPolicy::SHALLOW_COPY);

	public:
		virtual CMRObject* Clone() const override;
		virtual CMRObject* Copy(const CMRCopyPolicy& policy) const override;
		virtual bool IsSameKindAs(const CMRObject* obj) const override;
		virtual const char* ClassName() const override;

	public:
		virtual CMRNode* AsNode();
		virtual const CMRNode* AsNode() const;

		virtual CMRDrawable* AsDrawable();
		virtual const CMRDrawable* AsDrawable() const;

		virtual CMRGeometry* AsGeometry();
		virtual const CMRGeometry* AsGeometry() const;

		virtual CMRGroup* AsGroup();
		virtual const CMRGroup* AsGroup() const;

		virtual CMRTransform* AsTransform();
		virtual const CMRTransform* AsTransform() const;

		virtual CMRCamera* AsCamera();
		virtual const CMRCamera* AsCamera() const;

		virtual CMRSwitch* AsSwitch();
		virtual const CMRSwitch* AsSwitch() const;

		virtual CMRGeode* AsGeode();
		virtual const CMRGeode* AsGeode() const;

		virtual CMRTerrain* AsTerrain();
		virtual const CMRTerrain* AsTerrain() const;

	public:
		virtual void Accept(CMRNodeVisitor& nv);
		virtual void Ascend(CMRNodeVisitor& nv);
		virtual void Traverse(CMRNodeVisitor& nv);

		typedef vector<CMRGroup*> ParentList;

		const ParentList& GetParents() const;
		ParentList& GetParents();
		CMRGroup* GetParent(unsigned int index);
		const CMRGroup* GetParent(unsigned int index) const;
		unsigned int GetNumParents() const;

		CMRNodePathList GetParentalNodePaths(CMRNode* haltTraversalAtNode = 0) const;
		CMRMatrixList GetWorldMatrices(const CMRNode* haltTraversalAtNode = 0) const;

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
		unsigned int GetNumChildrenRequiringUpdateTraversal() const;



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

		unsigned int GetNumChildrenRequiringEventTraversal() const;

		void SetCullCallback(CMRCallback* cb);

		template<typename T>
		void SetCullCallback(const SmartPtr<T>& cb);

		CMRCallback* GetCullCallback();

		const CMRCallback* GetCullCallback() const;

		void AddCullCallback(CMRCallback* cb);

		template<typename T>
		void AddCullCallback(const SmartPtr<T>& cb);

		void RemoveCullCallback(CMRCallback* cb);

		template<typename T>
		void RemoveCullCallback(const SmartPtr<T>& cb);

		void SetCullActive(bool bActive);
		bool GetCullActive() const;

		unsigned int GetNumChildrenWithCullingDisabled() const;

		bool IsCullingActive() const;

		unsigned int GetNumChildrenWithOccluderNodes() const;

		bool ContainsOccluderNodes() const;

		void SetNodeMask(NodeMask nm);
		NodeMask GetNodeMask() const;

		void SetStateSet(CMRStateSet* pStateSet);
		
		template<typename T>
		void SetStateSet(const SmartPtr<CMRStateSet>& spStateSet);

		CMRStateSet* GetOrCreateStateSet();

		CMRStateSet* GetStateSet();
		const CMRStateSet* GetStateSet() const;


		typedef vector<string> DescriptionList;

		void SetDescriptions(const DescriptionList& descriptions);
		
		DescriptionList& GetDescriptions();
		
		const DescriptionList& GetDescriptions() const;

		const string& GetDescription(unsigned int index) const;

		string& GetDescription(unsigned int index);

		unsigned int GetNumDescriptions() const;

		void AddDescription(const string& descrition);

		void SetInitialBound(const CMRBoundingSphere& bs);

		void DirtyBound();

		const CMRBoundingSphere& GetInitialBound() const;

		const CMRBoundingSphere& GetBound() const;

		virtual CMRBoundingSphere ComputeBound() const;

		void SetComputeBoundingSphereCallback(ComputeBoundingSphereCallback* callback);

		template<typename T>
		void SetComputeBoundingSphereCallback(const SmartPtr<T>& sp);

		ComputeBoundingSphereCallback* GetComputeBoundingSphereCallback();

		const ComputeBoundingSphereCallback* GetComputeBoundingSphereCallback() const;

		virtual void ResizeGLObjectBuffers(unsigned int);
		virtual void ReleaseGLObjects(CMRState* pState = 0) const;
	
	protected:
		virtual ~CMRNode();

		void AddParent(CMRGroup* parent);
		void RemoveParent(CMRGroup* parent);

		void SetNumChildrenRequiringUpdateTraversal(unsigned int num);
		void SetNumChildrenRequiringEventTraversal(unsigned int num);
		void SetNumChildrenWithCullingDisabled(unsigned int num);
		void SetNumChildrenWithOccluderNodes(unsigned int num);
	protected:
		ParentList m_parents;
		SmartPtr<CMRCallback> m_spUpdateCallback;
		unsigned int m_uiNumChildrenRequiringUpdateTraversal;
		SmartPtr<CMRCallback> m_spEventCallback;
		unsigned int m_uiNumChildrenRequiringEventTraversal;
		SmartPtr<CMRCallback> m_spCullCallback;
		bool m_bCullActive;
		unsigned int m_uiNumChildrenWithCullingDisabled;
		unsigned int m_uiNumChildrenWithOccluderNodes;
		NodeMask m_nodeMask;
		SmartPtr<CMRStateSet> m_spStateSet;
		CMRBoundingSphere m_initialBound;
		mutable bool m_bBoundingSphereComputed;
		CMRBoundingSphere m_boundingSphere;
		SmartPtr<ComputeBoundingSphereCallback> m_spComputeBoundCallback;
	};
}
#endif // CMRNode_h__
