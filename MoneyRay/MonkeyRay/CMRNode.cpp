#include "CMRNode.h"

using namespace MR;

MR::CMRNode::CMRNode()
{
	//TODO: MR::CMRNode::CMRNode is not implemented

}

CMRObject* MR::CMRNode::Clone() const
{
	return new CMRNode();
}

CMRObject* MR::CMRNode::Copy(const CMRCopyPolicy& policy) const
{
	return new CMRNode(*this, policy);
}

bool MR::CMRNode::IsSameKindAs(const CMRObject* obj) const
{
	return dynamic_cast<const CMRNode*>(obj) != NULL;
}

const char* MR::CMRNode::ClassName() const
{
	return "CMRNode";
}

const CMRNode* MR::CMRNode::AsNode() const
{
	return this;
}

CMRNode* MR::CMRNode::AsNode()
{
	return this;
}

const CMRDrawable* MR::CMRNode::AsDrawable() const
{
	return 0;
}

CMRDrawable* MR::CMRNode::AsDrawable()
{
	return 0;
}

const CMRGeometry* MR::CMRNode::AsGeometry() const
{
	return 0;
}

CMRGeometry* MR::CMRNode::AsGeometry()
{
	return 0;
}

const CMRGroup* MR::CMRNode::AsGroup() const
{
	return 0;
}

CMRGroup* MR::CMRNode::AsGroup()
{
	return 0;
}

const CMRTransform* MR::CMRNode::AsTransform() const
{
	return 0;
}

CMRTransform* MR::CMRNode::AsTransform()
{
	return 0;
}

const CMRCamera* MR::CMRNode::AsCamera() const
{
	return 0;
}

CMRCamera* MR::CMRNode::AsCamera()
{
	return 0;
}

const CMRSwitch* MR::CMRNode::AsSwitch() const
{
	return 0;
}

CMRSwitch* MR::CMRNode::AsSwitch()
{
	return 0;
}

const CMRGeode* MR::CMRNode::AsGeode() const
{
	return 0;
}

CMRGeode* MR::CMRNode::AsGeode()
{
	return 0;
}

const CMRTerrain* MR::CMRNode::AsTerrain() const
{
	return 0;
}

CMRTerrain* MR::CMRNode::AsTerrain()
{
	return 0;
}

void MR::CMRNode::Accept(CMRNodeVisitor& nv)
{
	//TODO: MR::CMRNode::Accept is not implemented

}

void MR::CMRNode::Ascend(CMRNodeVisitor& nv)
{
	//TODO: MR::CMRNode::Ascend is not implemented

}

void MR::CMRNode::Traverse(CMRNodeVisitor& nv)
{
	//TODO: MR::CMRNode::Traverse is not implemented

}

CMRNode::ParentList& MR::CMRNode::GetParents()
{
	return m_parents;
}

const CMRNode::ParentList& MR::CMRNode::GetParents() const
{
	return m_parents;
}

const CMRGroup* MR::CMRNode::GetParent(unsigned int index) const
{
	return m_parents[index];
}

CMRGroup* MR::CMRNode::GetParent(unsigned int index)
{
	return m_parents[index];
}

unsigned int MR::CMRNode::GetNumParents() const
{
	return static_cast<unsigned int>(m_parents.size());
}

MR::CMRNodePathList MR::CMRNode::GetParentalNodePaths(CMRNode* haltTraversalAtNode /*= 0*/) const
{
	//TODO: MR::CMRNode::GetParentalNodePaths is not implemented

}

MR::CMRMatrixList MR::CMRNode::GetWorldMatrices(const CMRNode* haltTraversalAtNode /*= 0*/) const
{
	//TODO: MR::CMRNode::GetWorldMatrices is not implemented

}

void MR::CMRNode::SetUpdateCallback(CMRCallback* pUC)
{
	//TODO: MR::CMRNode::SetUpdateCallback is not implemented

}

template <typename T>
void MR::CMRNode::SetUpdateCallback(const SmartPtr<T>& spUC)
{
	SetUpdateCallback(spUC.Get());
}

const CMRCallback* MR::CMRNode::GetUpdateCallback() const
{
	return m_spUpdateCallback.Get();
}

CMRCallback* MR::CMRNode::GetUpdateCallback()
{
	return m_spUpdateCallback.Get();
}

template<typename T>
void MR::CMRNode::AddUpdateCallback(const SmartPtr<T>& spUC)
{
	AddUpdateCallback(spUC.Get());
}

void MR::CMRNode::AddUpdateCallback(CMRCallback* pc)
{
	if (pc != NULL)
	{
		if (m_spUpdateCallback.Valid())
		{
			m_spUpdateCallback->AddNestedCallback(pc);
		}
		else
		{
			SetUpdateCallback(pc);
		}
	}
}

template<typename T>
void MR::CMRNode::RemoveUpdateCallback(const SmartPtr<CMRCallback>& pCallback)
{
	RemoveUpdateCallback(pCallback.Get());
}

void MR::CMRNode::RemoveUpdateCallback(CMRCallback* pUC)
{
	if (pUC != NULL && m_spUpdateCallback.Valid())
	{
		if (m_spUpdateCallback == pUC)
		{
			SmartPtr<CMRCallback> newUpdateCallback = pUC->GetNestedCallback();
			pUC->SetNestedCallback((CMRCallback*)(nullptr));
			m_spUpdateCallback->SetUpdateCallback(newUpdateCallback.Get());
		}
		else
		{
			m_spUpdateCallback->RemoveNestedCallback(pUC);
		}
	}
}

unsigned int MR::CMRNode::GetNumChildrenRequiringUpdateTraversal() const
{
	return m_uiNumChildrenRequiringUpdateTraversal;
}

void MR::CMRNode::SetEventCallback(CMRCallback* cb)
{
	//TODO: MR::CMRNode::SetEventCallback is not implemented

}

template<typename T>
void MR::CMRNode::SetEventCallback(const SmartPtr<T>& cb)
{
	SetEventCallback(cb.Get());
}

const CMRCallback* MR::CMRNode::GetEventCallback() const
{
	return m_spEventCallback.Get();
}

CMRCallback* MR::CMRNode::GetEventCallback()
{
	return m_spEventCallback.Get();
}

template<typename T>
void MR::CMRNode::AddEventCallback(const SmartPtr<T>& cb)
{
	AddEventCallback(cb.Get());
}

void MR::CMRNode::AddEventCallback(CMRCallback* cb)
{
	if (cb != nullptr)
	{
		if (m_spEventCallback.Valid())
		{
			m_spEventCallback->AddNestedCallback(cb);
		}
		else
		{
			SetEventCallback(cb);
		}
	}
}

template<typename T>
void MR::CMRNode::RemoveEventCallback(const SmartPtr<T>& cb)
{
	RemoveEventCallback(cb.Get());
}

void MR::CMRNode::RemoveEventCallback(CMRCallback* cb)
{
	if (cb != nullptr && m_spEventCallback.Valid())
	{
		if (m_spEventCallback == cb)
		{
			SmartPtr<CMRCallback> newEventCallback = cb->GetNestedCallback();
			cb->SetNestedCallback(0);
			SetEventCallback(newEventCallback.Get());
		}
		else
		{
			m_spEventCallback->RemoveNestedCallback(cb);
		}
	}
}

unsigned int MR::CMRNode::GetNumChildrenRequiringEventTraversal() const
{
	return m_uiNumChildrenRequiringEventTraversal;
}

void MR::CMRNode::SetCullCallback(CMRCallback* cb)
{
	//TODO: MR::CMRNode::SetCullCallback is not implemented

}

template<typename T>
void MR::CMRNode::SetCullCallback(const SmartPtr<T>& cb)
{
	SetCullCallback(cb.Get());
}

const CMRCallback* MR::CMRNode::GetCullCallback() const
{
	return m_spCullCallback.Get();
}

CMRCallback* MR::CMRNode::GetCullCallback()
{
	return m_spCullCallback.Get();
}

template<typename T>
void MR::CMRNode::AddCullCallback(const SmartPtr<T>& cb)
{
	AddCullCallback(cb.Get());
}

void MR::CMRNode::AddCullCallback(CMRCallback* cb)
{
	if (cb != nullptr)
	{
		if (m_spCullCallback.Valid())
		{
			m_spCullCallback->AddNestedCallback(cb);
		}
		else
		{
			SetCullCallback(cb);
		}
	}
}

template<typename T>
void MR::CMRNode::RemoveCullCallback(const SmartPtr<T>& cb)
{
	RemoveCullCallback(cb.Get());
}

void MR::CMRNode::RemoveCullCallback(CMRCallback* cb)
{
	if (cb != nullptr && m_spCullCallback.Valid())
	{
		if (m_spCullCallback == cb)
		{
			SmartPtr<CMRCallback> newCullCallback = cb->GetNestedCallback();
			cb->SetNestedCallback(0);
			SetCullCallback(newCullCallback.Get());
		}
		else
		{
			m_spCullCallback->RemoveNestedCallback(cb);
		}
	}
}

void MR::CMRNode::SetCullActive(bool bActive)
{
	//TODO: MR::CMRNode::SetCullActive is not implemented

}

bool MR::CMRNode::GetCullActive() const
{
	return m_bCullActive;
}

unsigned int MR::CMRNode::GetNumChildrenWithCullingDisabled() const
{
	return m_uiNumChildrenWithCullingDisabled;
}

bool MR::CMRNode::IsCullingActive() const
{
	return m_uiNumChildrenWithCullingDisabled == 0 && m_bCullActive && GetBound().Valid();
}

unsigned int MR::CMRNode::GetNumChildrenWithOccluderNodes() const
{
	return m_uiNumChildrenWithOccluderNodes;
}

bool MR::CMRNode::ContainsOccluderNodes() const
{
	//TODO: MR::CMRNode::ContainsOccluderNodes is not implemented

}

void MR::CMRNode::SetNodeMask(NodeMask nm)
{
	m_nodeMask = nm;
}

MR::CMRNode::NodeMask MR::CMRNode::GetNodeMask() const
{
	return m_nodeMask;
}

void MR::CMRNode::SetStateSet(CMRStateSet* pStateSet)
{
	//TODO: MR::CMRNode::SetStateSet is not implemented

}

template<typename T>
void MR::CMRNode::SetStateSet(const SmartPtr<CMRStateSet>& spStateSet)
{
	SetStateSet(spStateSet.Get());
}

CMRStateSet* MR::CMRNode::GetOrCreateStateSet()
{
	//TODO: MR::CMRNode::GetOrCreateStateSet is not implemented

}

const CMRStateSet* MR::CMRNode::GetStateSet() const
{
	return m_spStateSet.Get();
}

CMRStateSet* MR::CMRNode::GetStateSet()
{
	return m_spStateSet.Get();
}

void MR::CMRNode::SetDescriptions(const DescriptionList& descriptions)
{
	//TODO: MR::CMRNode::SetDescriptions is not implemented

}

DescriptionList& MR::CMRNode::GetDescriptions()
{
	//TODO: MR::CMRNode::GetDescriptions is not implemented

}

const string& MR::CMRNode::GetDescription(unsigned int index) const
{
	//TODO: MR::CMRNode::GetDescription is not implemented

}

unsigned int MR::CMRNode::GetNumDescriptions() const
{
	//TODO: MR::CMRNode::GetNumDescriptions is not implemented

}

void MR::CMRNode::AddDescription(const string& descrition)
{
	//TODO: MR::CMRNode::AddDescription is not implemented

}

void MR::CMRNode::SetInitialBound(const CMRBoundingSphere& bs)
{
	m_initialBound = bs;
	DirtyBound();
}

void MR::CMRNode::DirtyBound()
{
	//TODO: MR::CMRNode::DirtyBound is not implemented

}

const CMRBoundingSphere& MR::CMRNode::GetInitialBound() const
{
	return m_initialBound;
}

const CMRBoundingSphere& MR::CMRNode::GetBound() const
{
	if (!m_bBoundingSphereComputed)
	{
		m_boundingSphere = m_initialBound;
		if (m_spComputeBoundCallback.Valid())
		{
			m_boundingSphere.ExpandBy(m_spComputeBoundCallback->ComputeBound(*this));
		}
		else
		{
			m_boundingSphere.ExpandBy(ComputeBound());
		}

		m_bBoundingSphereComputed = true;
	}

	return m_boundingSphere;
}

MR::CMRBoundingSphere MR::CMRNode::ComputeBound() const
{
	//TODO: MR::CMRNode::ComputeBound is not implemented

}

template<typename T>
void MR::CMRNode::SetComputeBoundingSphereCallback(const SmartPtr<T>& sp)
{
	SetComputeBoundingSphereCallback(sp.Get());
}

void MR::CMRNode::SetComputeBoundingSphereCallback(ComputeBoundingSphereCallback* callback)
{
	m_spComputeBoundCallback = callback;
}

const ComputeBoundingSphereCallback* MR::CMRNode::GetComputeBoundingSphereCallback() const
{
	return m_spComputeBoundCallback.Get();
}

ComputeBoundingSphereCallback* MR::CMRNode::GetComputeBoundingSphereCallback()
{
	return m_spComputeBoundCallback.Get();
}

void MR::CMRNode::ResizeGLObjectBuffers(unsigned int)
{
	//TODO: MR::CMRNode::ResizeGLObjectBuffers is not implemented

}

void MR::CMRNode::ReleaseGLObjects(CMRState* pState /*= 0*/) const
{
	//TODO: MR::CMRNode::ReleaseGLObjects is not implemented

}

MR::CMRNode::~CMRNode()
{
	//TODO: MR::CMRNode::~CMRNode is not implemented

}

void MR::CMRNode::AddParent(CMRGroup* parent)
{
	//TODO: MR::CMRNode::AddParent is not implemented

}

void MR::CMRNode::RemoveParent(CMRGroup* parent)
{
	//TODO: MR::CMRNode::RemoveParent is not implemented

}

void MR::CMRNode::SetNumChildrenRequiringUpdateTraversal(unsigned int num)
{
	//TODO: MR::CMRNode::SetNumChildrenRequiringUpdateTraversal is not implemented

}

void MR::CMRNode::SetNumChildrenRequiringEventTraversal(unsigned int num)
{
	//TODO: MR::CMRNode::SetNumChildrenRequiringEventTraversal is not implemented

}

void MR::CMRNode::SetNumChildrenWithCullingDisabled(unsigned int num)
{
	//TODO: MR::CMRNode::SetNumChildrenWithCullingDisabled is not implemented

}

void MR::CMRNode::SetNumChildrenWithOccluderNodes(unsigned int num)
{
	//TODO: MR::CMRNode::SetNumChildrenWithOccluderNodes is not implemented

}

string& MR::CMRNode::GetDescription(unsigned int index)
{
	//TODO: MR::CMRNode::GetDescription is not implemented

}

const DescriptionList& MR::CMRNode::GetDescriptions() const
{
	//TODO: MR::CMRNode::GetDescriptions is not implemented

}

MR::CMRNode::CMRNode(const CMRNode& node, const CMRCopyPolicy& policy /*= CMRCopyPolicy::SHALLOW_COPY*/)
{
	//TODO: MR::CMRNode::CMRNode is not implemented

}
