#include "CMRNode.h"
#include "CMRNodeVisitor.h"

using namespace MR;

MR::CMRNode::CMRNode() :
	m_parents(),
	m_children(),
	m_matTransform(vmath::mat4::identity())
{
	m_spEventCallback = new CMRCallback();
	m_spUpdateCallback = new CMRCallback();

}

CMRNode* MR::CMRNode::AsNode()
{
	return this;

}

const CMRNode* MR::CMRNode::AsNode() const
{
	return this;
}

CMRNode* MR::CMRNode::GetParent(unsigned int index)
{
	return m_parents[index];
}

unsigned int MR::CMRNode::GetNumParents() const
{
	return m_parents.size();
}

void MR::CMRNode::SetUpdateCallback(CMRCallback* pUC)
{
	if (m_spUpdateCallback == pUC)
	{
		return;
	}
	m_spUpdateCallback = pUC;
}

CMRCallback* MR::CMRNode::GetUpdateCallback()
{
	return m_spUpdateCallback.Get();

}

void MR::CMRNode::AddUpdateCallback(CMRCallback* pc)
{
	if (pc)
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

void MR::CMRNode::RemoveUpdateCallback(CMRCallback* pUC)
{
	if (pUC && m_spUpdateCallback.Valid())
	{
		if (pUC == m_spUpdateCallback)
		{
			SmartPtr<CMRCallback> new_nested_callback = m_spUpdateCallback->GetNestedCallback();
			pUC->SetNestedCallback(nullptr);
			SetUpdateCallback(new_nested_callback);
		}
		else
		{
			m_spUpdateCallback->RemoveNestedCallback(pUC);
		}
	}

}

void MR::CMRNode::SetEventCallback(CMRCallback* cb)
{
	if (m_spEventCallback == cb)
	{
		return;
	}
	m_spEventCallback = cb;
}

CMRCallback* MR::CMRNode::GetEventCallback()
{
	return m_spEventCallback.Get();
}

void MR::CMRNode::AddEventCallback(CMRCallback* cb)
{
	if (cb)
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

const CMRCallback* MR::CMRNode::GetEventCallback() const
{
	return m_spEventCallback.Get();

}

const CMRCallback* MR::CMRNode::GetUpdateCallback() const
{
	return m_spUpdateCallback.Get();

}

const CMRNode* MR::CMRNode::GetParent(unsigned int index) const
{
	if (index < GetNumParents())
	{
		return m_parents[index];
	}
	return nullptr;
}

CMRNode::ParentList& MR::CMRNode::GetParents()
{
	return m_parents;

}

const CMRNode::ParentList& MR::CMRNode::GetParents() const
{
	return m_parents;

}

void MR::CMRNode::RemoveEventCallback(CMRCallback* cb)
{
	if (cb && m_spEventCallback.Valid())
	{
		if (m_spEventCallback == cb)
		{
			SmartPtr<CMRCallback> new_nested_callback = m_spEventCallback->GetNestedCallback();
			cb->SetNestedCallback(nullptr);
			SetEventCallback(new_nested_callback);
		}
		else
		{
			m_spEventCallback->RemoveNestedCallback(cb);
		}
	}
}

void MR::CMRNode::AddTransform(const vmath::mat4& matrix)
{
	m_matTransform *= matrix;
}

vmath::mat4 MR::CMRNode::GetTransform() const
{
	return m_matTransform;
}

void MR::CMRNode::Accept(CMRNodeVisitor& nv)
{
	nv.Apply(*this);
}

void MR::CMRNode::Ascend(CMRNodeVisitor& nv)
{

}

void MR::CMRNode::Traverse(CMRNodeVisitor& nv)
{
	Accept(nv);
}

template<typename T>
bool MR::CMRNode::AddChild(const SmartPtr<T>& child)
{
	return AddChild(child.Get());
}

bool MR::CMRNode::AddChild(CMRNode* child)
{
	if (child)
	{
		m_children.push_back(child);
		child->AddParent(this);
		return true;
	}
	else
	{
		return false;
	}

}

template<typename T>
bool MR::CMRNode::InsertChild(unsigned int index, const SmartPtr<T>& child)
{
	return InsertChild(index, child.Get());
}

bool MR::CMRNode::InsertChild(unsigned int index, CMRNode* child)
{
	if (child)
	{
		if (index > m_children.size())
		{
			index = m_children.size();
			m_children.insert(m_children.begin() + index, child);
		}
		else
		{
			m_children.insert(m_children.begin() + index, child);
		}
		return true;
	}
	return false;
}

bool MR::CMRNode::RemoveChild(unsigned int pos, unsigned int numChildrenToRemove /*= 1*/)
{
	if (pos < m_children.size())
	{
		return RemoveChildren(pos, numChildrenToRemove);
	}
	return false;
}

bool MR::CMRNode::RemoveChildren(unsigned int pos, unsigned int numChildrenToRemove)
{
	if (pos < GetNumChildren() && numChildrenToRemove > 0)
	{
		if (pos + numChildrenToRemove > GetNumChildren())
		{
			m_children.erase(m_children.begin() + pos, m_children.end());
		}
		else
		{
			m_children.erase(m_children.begin() + pos, m_children.begin() + pos + numChildrenToRemove);
		}
		return true;
	}
	return false;
}

template<typename T, typename R>
bool MR::CMRNode::ReplaceChild(const SmartPtr<T>& oriChild, const SmartPtr<R>& newChild)
{
	return ReplaceChild(oriChild.Get(), newChild.Get());
}

unsigned int MR::CMRNode::GetNumChildren() const
{
	return m_children.size();
}

bool MR::CMRNode::SetChild(unsigned int index, CMRNode* newChild)
{
	if (index < GetNumChildren() && newChild)
	{
		SmartPtr<CMRNode> origNode = m_children[index];
		origNode->RemoveParent(this);
		m_children[index] = newChild;
		newChild->AddParent(this);
		return true;
	}
	else
	{
		return false;
	}

}

bool MR::CMRNode::ReplaceChild(CMRNode* oriChild, CMRNode* newChild)
{
	if (newChild == nullptr || oriChild == newChild)
	{
		return false;
	}
	unsigned int pos = GetChildIndex(oriChild);
	if (pos < GetNumChildren())
	{
		return SetChild(pos, newChild);
	}
	return false;

}

const CMRNode* MR::CMRNode::GetChild(unsigned int index) const
{
	if (index < GetNumChildren())
	{
		return m_children[index].Get();
	}
	return nullptr;
}

CMRNode* MR::CMRNode::GetChild(unsigned int index)
{
	if (index < GetNumChildren())
	{
		return m_children[index].Get();
	}
	return nullptr;
}

template <typename T>
bool MR::CMRNode::ContainsNode(const SmartPtr<T>& spNode)
{
	return ContainsNode(spNode.Get());
}

bool MR::CMRNode::ContainsNode(const CMRNode* pNode) const
{
	for (
		auto itr = m_children.begin();
		itr != m_children.end();
		++itr
		)
	{
		if ((*itr).Get() == pNode)
		{
			return true;
		}
	}
	return false;
}

unsigned int MR::CMRNode::GetChildIndex(CMRNode* pNode) const
{
	for (unsigned int i = 0; i < m_children.size(); ++i)
	{
		if (m_children[i].Get() == pNode)
		{
			return i;
		}
	}
	return static_cast<unsigned int> (m_children.size());
}

MR::CMRNode::CMRNode(const CMRNode& node)
{

}

MR::CMRNode::~CMRNode()
{

}

void MR::CMRNode::AddParent(CMRNode* parent)
{
	if (parent)
	{
		m_parents.push_back(parent);
	}

}

void MR::CMRNode::RemoveParent(CMRNode* parent)
{
	CMRNode::ParentList::iterator pitr = std::find(m_parents.begin(), m_parents.end(), parent);
	if (pitr != m_parents.end())
	{
		m_parents.erase(pitr);
	}

}

template<typename T>
void MR::CMRNode::RemoveEventCallback(const SmartPtr<T>& cb)
{
	RemoveEventCallback(cb.Get());

}

template<typename T>
void MR::CMRNode::AddEventCallback(const SmartPtr<T>& cb)
{
	AddEventCallback(cb.Get());

}

template<typename T>
void MR::CMRNode::SetEventCallback(const SmartPtr<T>& cb)
{
	SetEventCallback(cb.Get());

}

template<typename T>
void MR::CMRNode::RemoveUpdateCallback(const SmartPtr<CMRCallback>& pCallback)
{
	RemoveUpdateCallback(pCallback.Get());

}

template<typename T>
void MR::CMRNode::AddUpdateCallback(const SmartPtr<T>& spUC)
{
	AddUpdateCallback(spUC.Get());

}

template <typename T>
void MR::CMRNode::SetUpdateCallback(const SmartPtr<T>& spUC)
{
	SetUpdateCallback(spUC.Get());

}
