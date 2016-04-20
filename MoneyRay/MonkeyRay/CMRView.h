#ifndef CMRView_h__
#define CMRView_h__
#include "CMRViewBase.h"
#include "CMRTimer.h"
#include "CMROperationThread.h"
namespace MR
{
	class CMRDirector;
	class CMRScene;

	class CMRView :public CMRViewBase
	{
	public:
		CMRView();


	public:
		void Init();

		virtual CMRView* AsView();

		CMRDirector* GetDirector() const;

		virtual void Take(CMRView& view);

		virtual void SetStartTick(Timer_t startTick);
		Timer_t GetStartTick() const;

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
		CMRView(const CMRView& rhs):CMRViewBase(rhs){}

		CMRView& operator=(const CMRView& view) { return *this; }

		virtual ~CMRView() {}


	protected:
		virtual CMROperation* _CreateRender(CMRCamera* pCamera);


	protected:
		CMRDirector*		m_pDirector;
		Timer_t				m_startTick;
		SmartPtr<CMRScene>	m_spScene;
	};

	


}
#endif // CMRView_h__
