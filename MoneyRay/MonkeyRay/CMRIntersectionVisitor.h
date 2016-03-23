#ifndef CMRIntersectionVisitor_h__
#define CMRIntersectionVisitor_h__

#include "CMRRef.h"

namespace MR
{
	class CMRIntersectionVisitor;

	class CMRIntersector : public CMRRef
	{
	public:
		enum CoordinateFrame
		{
			WINDOW,
			PROJECTION,
			VIEW,
			MODEL
		};

		enum IntersectionLimit
		{
			NO_LIMIT,
			LIMIT_ONE_PER_DRAWABLE,
			LIMIT_ONE,
			LIMIT_NEAREST
		};

		enum PrecisionHint
		{
			USE_DOUBLE_CALCULATIONS,
			USE_FLOAT_CALCULATIONS
		};
	protected:
	private:
	};
}
#endif // CMRIntersectionVisitor_h__
