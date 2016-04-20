#ifndef CMRNodeVisitor_h__
#define CMRNodeVisitor_h__

#include "CMRObject.h"
namespace MR
{
	class CMRNodeVisitor : public virtual CMRObject
	{
	public:
		enum TraversalMode
		{
			TRAVERSE_NONE,
			TRAVERSE_PARENTS,
			TRAVERSE_ALL_CHILDREN,
			TRAVERSE_ACTIVE_CHILDREN
		};

		enum VisitorType
		{
			NODE_VISITOR = 0,
			UPDATE_VISITOR,
			EVENT_VISITOR,
			COLLECT_OCCLUDER_VISITOR,
			CULL_VISITOR,
			INTERSECTION_VISITOR
		};

	protected:
	private:
	};
}
#endif // CMRNodeVisitor_h__
