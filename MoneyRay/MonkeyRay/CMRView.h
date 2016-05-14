#ifndef CMRView_h__
#define CMRView_h__
#include "CMRTimer.h"
#include "CMROperationThread.h"
#include "CMRGraphicsWindow.h"
#include "CMRFrameStamp.h"
#include "CMRCamera.h"
namespace MR
{
	class CMRDirector;
	class CMRScene;

	class CMRView : public CMRRef, public CMRGraphicsWindow
	{
	public:
		CMRView();
		CMRView(int x, int y, int width, int height, bool bFullScreen, string windowName);

	public:
		void Init();

		virtual CMRView* AsView();

		void SetDirector(CMRDirector* pDirector);
		CMRDirector* GetDirector() const;

		virtual void Take(CMRView& view);

		virtual void SetStartTick(Timer_t startTick);
		Timer_t GetStartTick() const;

		void SetCamera(CMRCamera* camera);
		CMRCamera* GetCamera();
		const CMRCamera* GetCamera() const;

		void SetFrameStamp(CMRFrameStamp* fs);
		CMRFrameStamp* GetFrameStamp();
		const CMRFrameStamp* GetFrameStamp() const;

		CMRScene* GetScene();
		const CMRScene* GetScene() const;
		virtual void SetSceneData(CMRNode* pScene);
		template<typename T>
		void SetSceneData(const SmartPtr<T>& spScene);
		CMRNode* GetSceneData();
		const CMRNode* GetSceneData() const;

		void Home();

		void AssignSceneDataToCameras();

		
	protected:
		CMRView(const CMRView& rhs){}

		CMRView& operator=(const CMRView& view) { return *this; }

		virtual ~CMRView();


	protected:
		virtual CMROperation* _CreateRender(CMRCamera* pCamera);


	protected:
		CMRDirector*		m_pDirector;
		Timer_t				m_startTick;
		SmartPtr<CMRCamera> m_spCamera;
		SmartPtr<CMRFrameStamp> m_spFrameStamp;
		SmartPtr<CMRScene>	m_spScene;
	};

	


}
#endif // CMRView_h__
