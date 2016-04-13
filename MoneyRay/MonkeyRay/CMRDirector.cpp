#include "CMRDirector.h"
#include "CMRGraphicsContext.h"
#include "CMRRender.h"
#include "CMRView.h"
#include "CMRNodeVisitor.h"
#include "CMRCameraManipulator.h"
#include "CMRMemManager.h"
#include "CMRDisplaySettings.h"
#include "CMRState.h"
#include "CMRNode.h"

using namespace MR;

MR::CMRDirector::CMRDirector(CMRView* pView)
	: m_bFirstFrame(true),
	m_bDone(false),
	m_dRunMaxFrameRate(60.0),
	m_spView(pView)
{

}

const char* MR::CMRDirector::ClassName() const
{
	return "CMRDirector";
}

CMRObject* MR::CMRDirector::Clone() const
{
	return nullptr;
}

CMRObject* MR::CMRDirector::Copy(const CMRCopyPolicy& policy) const
{
	return nullptr;
}

MR::CMRDirector::~CMRDirector()
{

}

void MR::CMRDirector::SetDirectorStats(CMRStats* stats)
{

}

CMRStats* MR::CMRDirector::GetDirectorStats()
{

}

void MR::CMRDirector::AddView(const CMRView* view)
{
	if (view == nullptr) return;
	m_spView = const_cast<CMRView*>(view);
}

bool MR::CMRDirector::IsRealized()
{
	CMRGraphicsContext* pContext = GetContext();
	if (pContext)
	{
		return pContext->IsRealized();
	}
	return false;
}

void MR::CMRDirector::Realize()
{
	CMRGraphicsContext* pContext = GetContext();
	if (!pContext)
	{
		m_bDone = true;
		return;
	}
	int maxBufferObjectPoolSize = 2;
	int maxBufferObjectPoolSize = 4;

	CMRState* pState = pContext->GetState();
	pState->SetMaxTexturePoolSize(maxBufferObjectPoolSize);
	pState->SetMaxBufferObjectPoolSize(maxBufferObjectPoolSize);

	pContext->Realize();

	if (!pContext->IsRealized())
	{
		m_bDone = true;
		return;
	}

	m_spView->SetStartTick(CMRTimer::Instance()->GetStartTick());

	CMRNode* pNode = GetScene()->GetSceneData();
	pNode->ResizeGLObjectBuffers(CMRDisplaySettings::Instance()->GetMaxNumberOfGraphicsContexts());
}

#if MR_USE_MULTITHREAD
void MR::CMRDirector::StartThreading()
{

}

void MR::CMRDirector::StopThrading()
{

}
#endif

bool MR::CMRDirector::Done() const
{
	return m_bDone;
}

void MR::CMRDirector::SetDone( bool bDone )
{
	m_bDone = bDone;
}

void MR::CMRDirector::SetEventVisitor(const CMREventVisitor* ev)
{
	m_spEventVisitor = const_cast<CMREventVisitor*>(ev);
}

CMREventVisitor* MR::CMRDirector::GetEventVisitor()
{
	return m_spEventVisitor.Get();
}

void MR::CMRDirector::SetUpdateVisitor(const CMRUpdateVisitor* uv)
{
	m_spUpdateVisitor = const_cast<CMRUpdateVisitor*>(uv);
}

CMRUpdateVisitor* MR::CMRDirector::GetUpdateVisitor()
{
	return m_spUpdateVisitor.Get();
}

void MR::CMRDirector::SetUpdateOperations(const CMROperationQueue* uo)
{
	m_spUpdateOperations = const_cast<CMROperationQueue*> (uo);
}

CMROperationQueue* MR::CMRDirector::GetUpdateOperations()
{
	return m_spUpdateOperations.Get();
}

void MR::CMRDirector::AddUpdateOperation(const CMROperation* op)
{
	if (!op)
	{
		return;
	}
	if (!m_spUpdateOperations.Valid())
	{
		m_spUpdateOperations = new CMROperationQueue;
	}
	m_spUpdateOperations->Add(op);
}

void MR::CMRDirector::RemoveUpdateOperation(const CMROperation* op)
{
	if (!op)
	{
		return;
	}
	if (m_spUpdateOperations.Valid())
	{
		m_spUpdateOperations->Remove(op);
	}
}

void MR::CMRDirector::SetRealizeOperation(const CMROperation* op)
{
	m_spRealizeOperation = const_cast<CMROperation*>(op);
}

CMROperation* MR::CMRDirector::GetRealizeOperation() const
{
	return m_spRealizeOperation.Get();
}

void MR::CMRDirector::SetIncrementalCompileOperation(const CMRIncrementalCompileOperation* op)
{

}

CMRIncrementalCompileOperation* MR::CMRDirector::GetIncrementalCompileOperation() const
{

}

void MR::CMRDirector::SetMaxFrameRate(double dFrameRate)
{
	m_dRunMaxFrameRate = dFrameRate;
}

double MR::CMRDirector::GetMaxFrameRate() const
{
	return m_dRunMaxFrameRate;
}

int MR::CMRDirector::Run()
{
	if (!IsRealized())
	{
		Realize();
	}

	while (!Done())
	{
		Frame();
	}
}

bool MR::CMRDirector::CheckEvents()
{

}

void MR::CMRDirector::Frame()
{
	if (m_bDone)
	{
		return;
	}

	if (m_bFirstFrame)
	{
		DirectorInit();
		if (!IsRealized())
		{
			Realize();
		}
		m_bFirstFrame = false;
	}
	Advance();

	EventTraversal();
	UpdateTraversal();
	RenderingTraversal();
}

void MR::CMRDirector::Advance()
{
	if (m_bDone)
	{
		return;
	}
	CMRView* pView = m_spView.Get();
	GetFrameStamp()->SetFrameNumber(CMRTimer::Instance()->DeltaS(pView->GetStartTick(), CMRTimer::Instance()->Tick()));

	GetFrameStamp()->SetSimulationTime(GetFrameStamp()->GetReferenceTime());

	CMRMemManager* pmm = CMRRef::GetMemManager();
	if (pmm)
	{
		pmm->Flush();
		pmm->SetCurrentFrameNumber(GetFrameStamp()->GetFrameNumber());
	}
}

void MR::CMRDirector::EventTraversal()
{
	if (m_bDone)
	{
		return;
	}

	double dCutOffTime = GetFrameStamp()->GetReferenceTime();

}

void MR::CMRDirector::UpdateTraversal()
{
	if (m_bDone)
	{
		return;
	}

	if (!m_spUpdateVisitor.Valid())
	{
		return;
	}

	m_spUpdateVisitor->Reset();
	m_spUpdateVisitor->SetFrameStamp(GetDirectorFrameStamp());
	unsigned int uiFrameNumber = GetDirectorFrameStamp()->GetFrameNumber();
	m_spUpdateVisitor->SetTraversalNumber(GetDirectorFrameStamp()->GetFrameNumber());

	CMRScene* pScene = m_spView->GetScene();
	pScene->UpdateSceneGraph();

	/*
	// if we have a shared state manager prune any unused entries
	if (osgDB::Registry::instance()->getSharedStateManager())
		osgDB::Registry::instance()->getSharedStateManager()->prune();

	// update the Registry object cache.
	osgDB::Registry::instance()->updateTimeStampOfObjectsInCacheWithExternalReferences(*getFrameStamp());
	osgDB::Registry::instance()->removeExpiredObjectsInCache(*getFrameStamp());
	*/

	if (m_spUpdateOperations.Valid())
	{
		m_spUpdateOperations->RunOperations(this);
	}

	if (m_spIncrementalCompileOperation.Valid())
	{
		m_spIncrementalCompileOperation->MergeCompiledSubgraphs(GetDirectorFrameStamp());
	}

	{
		CMRNodeVisitor::TraversalMode tm = m_spUpdateVisitor->GetTraversalMode();
		m_spUpdateVisitor->SetTraversalMode(CMRNodeVisitor::TraversalMode::TRAVERSE_NONE);
		CMRCamera* pCamera = GetCamera();
		if (pCamera && pCamera->GetUpdateCallback())
		{
			CMRUpdateVisitor* pUpdateVisitor = m_spUpdateVisitor.Get();
			pCamera->Accept(*pUpdateVisitor);
		}

		m_spUpdateVisitor->SetTraversalMode(tm);
	}

	CMRCameraManipulator* cm = m_spView->GetManipulator();
	if (cm)
	{
		CMRCamera* pCamera = GetCamera();
		cm->UpdateCamera(*pCamera);
	}
}

void MR::CMRDirector::RenderingTraversal()
{
	CMRGraphicsContext* pContext = GetContext();

	CheckWindowStatus(pContext);
	if (m_bDone) return;

	double dBeginRenderingTraversal = ElapsedTime();

	CMRFrameStamp* pFrameStamp = GetDirectorFrameStamp();

	CMRScene* pScene = GetScene();
	assert(pScene != nullptr);
	if (pScene)
	{
#if MR_USE_MULTITHREAD
		CMRDatabasePager* dp = pScene->GetDataBasePager();
		if (dp)
		{
			dp->SignalBeginFrame(pFrameStamp);
		}

		CMRImagePager* ip = pScene->GetImagePager();
		if (ip)
		{
			ip->SignalBeginFrame(pFrameStamp);
		}
#endif
		//TODO: scene data update is to be done.
		pScene->UpdateSceneData();
		if (pScene->GetSceneData())
		{
			pScene->GetSceneData()->GetBound();
		}
	}
	else
	{
		return;
	}

	CMRCamera* pCamera = GetCamera();
	CMRRender* pRender = dynamic_cast<CMRRender*> (pCamera->GetRender());
	assert(pRender != nullptr);
	if (pRender)
	{
		pRender->CullDraw();
	}
	else
	{
		return;
	}

	pContext->SwapBuffers();

}

CMRCamera* MR::CMRDirector::GetCamera() const
{
	assert(m_spView.Get() != nullptr);
	if (!m_spView.Valid())
	{
		return nullptr;
	}
	return m_spView->GetCamera();
}

CMRGraphicsContext* MR::CMRDirector::GetContext() const
{
	assert(m_spView.Get() != nullptr);
	if (!m_spView.Valid())
	{
		return nullptr;
	}
	CMRCamera* pCamera = m_spView->GetCamera();
	assert(pCamera != nullptr);
	if (!pCamera)
	{
		return nullptr;
	}
	return pCamera->GetGraphicsContext();
}

CMRGraphicsWindow* MR::CMRDirector::GetWindow() const
{
	CMRGraphicsWindow* gw = dynamic_cast<CMRGraphicsWindow*>(GetContext());
	return gw;
}

CMRFrameStamp* MR::CMRDirector::GetFrameStamp() const
{
	return m_spView->GetFrameStamp();
}

MR::Timer_t MR::CMRDirector::GetStartTick() const
{
	return m_spView->GetStartTick();
}

#if MR_USE_MULTITHREAD
void MR::CMRDirector::GetThreads(Threads& threads, bool bOnlyActive /*= true*/)
{

}
#endif

#if MR_USE_MULTITHREAD
void MR::CMRDirector::GetOperationThreads(OperationThreads& threads, bool bOnlyActive /*= true*/)
{

}
#endif

CMRScene* MR::CMRDirector::GetScene() const
{
	return GetView()->GetScene();
}

MR::CMRView* MR::CMRDirector::GetView() const
{
	return m_spView.Get();
}

void MR::CMRDirector::CheckWindowStatus()
{
	CheckWindowStatus(GetContext());
}

void MR::CMRDirector::CheckWindowStatus(const CMRGraphicsContext* ptr)
{
	if (!ptr)
	{
		m_bDone = true;
#if MR_USE_MULTITHREAD
		if (AreThreadsRunning())
		{
			StopThrading();
		}
#endif
	}
}

double MR::CMRDirector::ElapsedTime()
{

}

void MR::CMRDirector::DirectorConstructorInit()
{
	m_spEventVisitor = new CMREventVisitor;
	m_spEventVisitor->SetActionAdapter(m_spView.Get());
	m_spEventVisitor->SetFrameStamp(GetFrameStamp());

	m_spUpdateVisitor = new CMRUpdateVisitor;
	m_spUpdateVisitor->SetFrameStamp(GetFrameStamp());

}

void MR::CMRDirector::MakeCurrent(CMRGraphicsContext* gc)
{

}

void MR::CMRDirector::ReleaseContext()
{

}

void MR::CMRDirector::DirectorInit()
{
	m_spView->Init();
}

const CMROperationQueue* MR::CMRDirector::GetUpdateOperations() const
{
	return m_spUpdateOperations.Get();
}

const CMRUpdateVisitor* MR::CMRDirector::GetUpdateVisitor() const
{
	return m_spUpdateVisitor.Get();
}

const CMREventVisitor* MR::CMRDirector::GetEventVisitor() const
{
	return m_spEventVisitor.Get();
}

const CMRStats* MR::CMRDirector::GetDirectorStats() const
{

}

