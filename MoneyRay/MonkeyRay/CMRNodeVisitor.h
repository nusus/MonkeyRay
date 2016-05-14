#ifndef CMRNodeVisitor_h__
#define CMRNodeVisitor_h__

#include "CMRObject.h"
#include "CMRNode.h"
namespace MR
{
	class CMRNodeVisitor : public virtual CMRObject
	{
	public:
		enum TraversalMode
		{
			T
		};
	public:
		virtual void Traverse(CMRNode& node);

		virtual void Apply(CMRNode& node);
		virtual void Apply(CMRCamera& node);
		virtual void Apply(CMRDrawable& node);
	};
}
#endif // CMRNodeVisitor_h__
