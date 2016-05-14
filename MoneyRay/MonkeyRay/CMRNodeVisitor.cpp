#include "CMRNodeVisitor.h"

using namespace MR;

void MR::CMRNodeVisitor::Traverse(CMRNode& node)
{
	node.Traverse(*this);
}

void MR::CMRNodeVisitor::Apply(CMRNode& node)
{

}

void MR::CMRNodeVisitor::Apply(CMRDrawable& node)
{

}

void MR::CMRNodeVisitor::Apply(CMRCamera& node)
{

}
