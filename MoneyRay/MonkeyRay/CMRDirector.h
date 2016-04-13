#ifndef CMRDirector_h__
#define CMRDirector_h__

#include "CMRObject.h"
#include "CMRStats.h"
#include "CMREventVisitor.h"
#include "CMRUpdateVisitor.h"
#include "CMROperationThread.h"
#include "CMRIncrementalCompileOperation.h"
#include "CMRCamera.h"
#include "CMRGraphicsContext.h"
#include "CMRGraphicsWindow.h"
#include "CMRScene.h"
#include "CMRFrameStamp.h"
#include "CMRTimer.h"
#include "SmartPtr.h"
#include "WeakPtr.h"

namespace MR
{
	class CMRView;


	class CMRDirector : public CMRObject 
	{
	public:

		static CMRDirector& InstanceWithView(CMRView* pView)
		{
			static CMRDirector ret(pView);
			return ret;
		}

		virtual const char* ClassName() const override;

		virtual ~CMRDirector();

		virtual void SetDirectorStats(CMRStats* stats);
		virtual CMRStats* GetDirectorStats();
		virtual const CMRStats* GetDirectorStats() const;

		void AddView(const CMRView* view);

		template<typename T>
		void AddView(const SmartPtr<T>& view) { AddView(view.Get()); }

		virtual bool IsRealized();
		virtual void Realize();

#if MR_USE_MULTITHREAD
		virtual bool AreThreadsRunning();
		virtual void StartThreading();
		virtual void StopThrading();
#endif

		bool Done() const;
		void SetDone(bool bDone);

		void SetEventVisitor(const CMREventVisitor* ev);
		CMREventVisitor* GetEventVisitor();
		const CMREventVisitor* GetEventVisitor() const;

		void SetUpdateVisitor(const CMRUpdateVisitor* uv);
		CMRUpdateVisitor* GetUpdateVisitor();
		const CMRUpdateVisitor* GetUpdateVisitor() const;

		void SetUpdateOperations(const CMROperationQueue* uo);
		CMROperationQueue* GetUpdateOperations();
		const CMROperationQueue* GetUpdateOperations() const;

		void AddUpdateOperation(const CMROperation* op);
		void RemoveUpdateOperation(const CMROperation* op);

		void SetRealizeOperation(const CMROperation* op);
		CMROperation* GetRealizeOperation() const;

		void SetIncrementalCompileOperation(const CMRIncrementalCompileOperation* op);
		CMRIncrementalCompileOperation* GetIncrementalCompileOperation() const;

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

		virtual CMRGraphicsWindow* GetWindow() const;


		virtual CMRFrameStamp* GetFrameStamp() const;

		virtual Timer_t GetStartTick() const;
#if MR_USE_MULTITHREAD
		typedef vector<std::thread*> Threads;
		virtual void GetThreads(Threads& threads, bool bOnlyActive = true);
#endif

#if MR_USE_MULTITHREAD
		typedef vector<CMROperationThread*> OperationThreads;
		virtual void GetOperationThreads(OperationThreads& threads, bool bOnlyActive = true);
#endif

		virtual CMRScene* GetScene() const;

		virtual CMRView* GetView() const;

		void CheckWindowStatus();

		void CheckWindowStatus(const CMRGraphicsContext* ptr);

		virtual double ElapsedTime();

		CMRFrameStamp* GetDirectorFrameStamp()
		{
			return m_spView->GetFrameStamp();
		}

	protected:
		CMRDirector(CMRView* pView);
		void DirectorConstructorInit();

		friend class CMRView;

		void MakeCurrent(CMRGraphicsContext* gc);
		void ReleaseContext();

		virtual void  DirectorInit();

		virtual CMRObject* Clone() const override;

		virtual CMRObject* Copy(const CMRCopyPolicy& policy) const override;
		//META_OBJECT(MonkeyRay, CMRDirector);

	protected:
		bool m_bFirstFrame;
		bool m_bDone;
#if MR_USE_MULTITHREAD
		bool m_bThreadsRunning;
#endif
		char m_bPadding[2];
		double m_dRunMaxFrameRate;
		
		SmartPtr<CMRView> m_spView;

		SmartPtr<CMROperation> m_spRealizeOperation;
		
		SmartPtr<CMREventVisitor> m_spEventVisitor;

		SmartPtr<CMROperationQueue> m_spUpdateOperations;
		SmartPtr<CMRUpdateVisitor> m_spUpdateVisitor;
			
		SmartPtr<CMRIncrementalCompileOperation> m_spIncrementalCompileOperation;

		WeakPtr<CMRGraphicsContext> m_wpCurrentContext;

		SmartPtr<CMRStats> m_spStates;

	private:
		CMRDirector& operator = (const CMRDirector&) { return *this; }
		
	};
}
#endif // CMRDirector_h__
