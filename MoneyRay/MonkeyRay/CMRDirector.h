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
		CMRDirector();
		CMRDirector(const  CMRDirector& dir, const CMRCopyPolicy& policy = CMRCopyPolicy::SHALLOW_COPY);

		META_OBJECT(MonkeyRay, CMRDirector);

		virtual ~CMRDirector();

		virtual void SetDirectorStats(CMRStats* stats);
		virtual CMRStats* GetDirectorStats();
		virtual const CMRStats* GetDirectorStats() const;

		void AddView(const CMRView* view);

		template<typename T>
		void AddView(const SmartPtr<T>& view) { AddView(view.Get()); }

		virtual bool IsRealized();
		virtual void Realize();

		virtual void 
		virtual void StartThreading();
		virtual void StopThrading();

		virtual void SetStartTick(Timer_t tick);

		bool Done() const;
		void SetDone();

		void SetEventVisitor(const CMREventVisitor* ev);
		CMREventVisitor* GetEventVisitor();
		const CMREventVisitor* GetEventVisitor() const;

		void SetQuitEventSetsDone(bool bFlag);
		bool GetQuitEventSetsDone() const;

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

		virtual int run();

		virtual bool CheckEvents();

		virtual void Frame();

		virtual void Advance();

		virtual void EventTraversal();
		virtual void UpdateTraversal();
		virtual void RenderingTraversal();

		virtual CMRCamera* GetCamera() const;

		virtual CMRGraphicsContext* GetContext() const;

		virtual CMRGraphicsWindow* GetWindow() const;

		typedef vector<std::thread*> Threads;
		virtual void GetThreads(Threads& threads, bool bOnlyActive = true);

		typedef vector<CMROperationThread*> OperationThreads;
		virtual void GetOperationThreads(OperationThreads& threads, bool bOnlyActive = true);

		virtual CMRScene* GetScene() const;

		virtual CMRView* GetView() const;

		void CheckWindowStatus();

		void CheckWindowStatus(const CMRGraphicsContext* ptr);

		virtual double ElapsedTime();

		virtual CMRFrameStamp* GetDirectorFrameStamp();
		virtual const CMRFrameStamp* GetDirectorFrameStamp() const;

	protected:
		void DirectorConstructorInit();

		friend class CMRView;

		void MakeCurrent(CMRGraphicsContext* gc);
		void ReleaseContext();

		virtual void  DirectorInit();

	protected:
		bool m_bFirstFrame;
		bool m_bDone;
		bool m_bThreadsRunning;
		bool m_bPadding;
		double m_dRunMaxFrameRate;
		
		SmartPtr<CMRView> m_spView;
		
		SmartPtr<CMROperationQueue> m_spUpdateOperations;
		SmartPtr<CMRUpdateVisitor> m_spUpdateVisitor;
		
		SmartPtr<CMREventVisitor> m_spEventVisitor;
		
		SmartPtr<CMROperation> m_spRealizeOperation;

		SmartPtr<CMRIncrementalCompileOperation> m_spIncrementalCompileOperation;

		WeakPtr<CMRGraphicsContext> m_wpCurrentContext;

		SmartPtr<CMRStats> m_spStates;
		Timer_t m_startTick;
		SmartPtr<CMRFrameStamp> m_spFrameStamp;

	private:
		CMRDirector& operator = (const CMRDirector&) { return *this; }
	};
}
#endif // CMRDirector_h__
