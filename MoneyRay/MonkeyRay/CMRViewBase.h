#ifndef CMRViewBase_h__
#define CMRViewBase_h__

#include "CMRObject.h"
#include "CMRCamera.h"
#include "CMRFrameStamp.h"

namespace MR
{
	class CMRViewBase : public CMRObject
	{
	public:

		CMRViewBase();

		virtual void Take(CMRViewBase& view);

		void SetCamera(CMRCamera* camera);
		CMRCamera* GetCamera();
		const CMRCamera* GetCamera() const;

		void SetFrameStamp(CMRFrameStamp* fs);
		CMRFrameStamp* GetFrameStamp();
		const CMRFrameStamp* GetFrameStamp() const;
	protected:
		CMRViewBase(const CMRViewBase&) {}
		CMRViewBase& operator=(const CMRViewBase&) { return *this; }
		virtual ~CMRViewBase();
		virtual CMROperation* _CreateRender(CMRCamera*) { return nullptr; }

	protected:
		SmartPtr<CMRCamera> m_spCamera;
		SmartPtr<CMRFrameStamp> m_spFrameStamp;
	};
}
#endif // CMRViewBase_h__
