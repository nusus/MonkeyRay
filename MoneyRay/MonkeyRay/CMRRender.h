#ifndef CMRRender_h__
#define CMRRender_h__
#include "CMROperationThread.h"
#include "SmartPtr.h"
#include "CMRObject.h"

namespace MR
{
	class CMRCamera;
	class CMRRenderStage;
	class CMRStateGraph;
	class CMRRender : public CMROperation
	{
	public:
		CMRRender(CMRCamera* pCamera);

		void Cull();

		void CullDraw();

		void Draw();

		virtual void operator()(CMRObject* obj) override;

	protected:
		CMRCamera* m_wpCamera;

		SmartPtr<CMRStateGraph> m_spStateGraph;
		SmartPtr<CMRRenderStage> m_spRenderStage;
	};
}

#endif // CMRRender_h__
