#ifndef CMRViewBase_h__
#define CMRViewBase_h__

#include "CMRObject.h"
#include "CMRGraphicsThread.h"
#include "CMRLight.h"
#include "CMRCamera.h"
#include "CMRFrameStamp.h"

namespace MR
{
	class CMRViewBase : public CMRObject
	{
	public:
		enum LightMode
		{
			NO_LIGHT,
			HEADLIGHT,
			SKY_LIGHT
		};
	public:

		CMRViewBase();
		CMRViewBase(const CMRViewBase& vb, const CMRCopyPolicy& policy = CMRCopyPolicy::SHALLOW_COPY);

		META_OBJECT(MonkeyRay, CMRViewBase);

		virtual void Take(CMRViewBase& view);

		void SetLightingMode(LightMode lightingMode);
		LightMode GetLightingMode() const;

		void SetLight(CMRLight* light);
		CMRLight* GetLight();
		const CMRLight* GetLight() const;

		void SetCamera(CMRCamera* camera);
		CMRCamera* GetCamera();
		const CMRCamera* GetCamera() const;

		void SetFrameStamp(CMRFrameStamp* fs);
		CMRFrameStamp* GetFrameStamp();
		const CMRFrameStamp* GetFrameStamp() const;
	protected:
		virtual ~CMRViewBase();

		virtual CMRGraphicsOperation* CreateRender(CMRCamera*) { return nullptr; }

	protected:
		LightMode m_lightMode;
		SmartPtr<CMRLight> m_spLight;
		SmartPtr<CMRCamera> m_spCamera;
		SmartPtr<CMRFrameStamp> m_spFrameStamp;
	};
}
#endif // CMRViewBase_h__
