#ifndef CMRRenderOperation_h__
#define CMRRenderOperation_h__
#include "CMRPrerequisites.h"
#include "CMROperationThread.h"
#include "CMRObject.h"
#include "CMRDrawable.h"
namespace MR
{
	class CMRRenderOperation : public CMROperation
	{
	public:
		virtual void operator ()(CMRObject* obj) override
		{
			
		}

		virtual void operator()(CMRDrawable& drawable) = 0;

	};

}
#endif // CMRRenderOperation_h__
