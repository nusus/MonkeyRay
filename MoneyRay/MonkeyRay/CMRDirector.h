#ifndef CMRDirector_h__
#define CMRDirector_h__

#include "CMRObject.h"
#include "CMROperationThread.h"
#include "CMRCamera.h"
#include "CMRScene.h"
#include "CMRFrameStamp.h"
#include "CMRTimer.h"
#include "SmartPtr.h"
#include "CMRGraphicsContext.h"

namespace MR
{
	class CMRView;

	class CMRDirector : public CMRObject 
	{
	public:
		static CMRDirector* Instance(CMRView* pView);

		virtual ~CMRDirector();


	public:
		void AddView(const CMRView* view);

		template<typename T>
		void AddView(const SmartPtr<T>& view);

		virtual bool IsRealized();

		virtual void Realize();

		bool Done() const;
		void SetDone(bool bDone);

		void SetRealizeOperation(const CMROperation* op);

		CMROperation* GetRealizeOperation() const;

		void SetMaxFrameRate(double dFrameRate);

		double GetMaxFrameRate() const;

		virtual int Run();

		virtual bool CheckEvents();

		virtual void Frame();

		virtual void Advance();

		virtual void EventTraversal();

		virtual void UpdateTraversal();

		virtual void RenderingTraversal();

		virtual CMRCamera* GetCamera() const;

		virtual CMRGraphicsContext* GetContext() const;

		virtual CMRFrameStamp* GetFrameStamp() const;

		virtual Timer_t GetStartTick() const;

		virtual CMRScene* GetScene() const;

		virtual CMRView* GetView() const;

		void CheckWindowStatus();

		void CheckWindowStatus(const CMRGraphicsContext* ptr);

		virtual double ElapsedTime();

		CMRFrameStamp* GetDirectorFrameStamp();


	protected:
		friend class CMRView;


	protected:
		CMRDirector(CMRView* pView);
		CMRDirector(const CMRDirector& rhs) {}
		CMRDirector& operator=(const CMRDirector& rhs) { return *this; }


	protected:
		void _DirectorConstructorInit();

		virtual void  _DirectorInit();


	protected:
		bool					m_bFirstFrame;
		bool					m_bDone;
		char					m_bPadding[2];
		double					m_dRunMaxFrameRate;		
		SmartPtr<CMRView>		m_spView;
		SmartPtr<CMROperation>	m_spRealizeOperation;
		CMRGraphicsContext*		m_wpCurrentContext;


	private:
		CMRDirector& operator = (const CMRDirector&);	
	};
}
#endif // CMRDirector_h__
