#ifndef CMRDrawable_h__
#define CMRDrawable_h__
#include "CMRNode.h"
namespace MR
{
	class CMRDrawable : public CMRNode
	{
	public:
		void Draw()
		{
			DrawImplemention();
		}

		virtual void DrawImplemention()
		{

		}
	protected:
	private:
	};
}
#endif // CMRDrawable_h__
