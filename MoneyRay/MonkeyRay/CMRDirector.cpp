#include "CMRDirector.h"
#include "CMRMemManager.h"
#include "CMRRender.h"

using namespace MR;

MR::CMRDirector::CMRDirector(CMRView* pView)
	: m_bFirstFrame(true),
	m_bDone(false),
	m_dRunMaxFrameRate(60.0),
	m_spView(pView)
{

}

CMRDirector* MR::CMRDirector::Instance(CMRView* pView)
{
	static CMRDirector ret(pView);
	return &ret;
}

CMRDirector& MR::CMRDirector::operator=(const CMRDirector&)
{
	return *this;
}

MR::CMRDirector::~CMRDirector()
{

}


void MR::CMRDirector::AddView(const CMRView* view)
{
	if (view == nullptr) return;
	m_spView = const_cast<CMRView*>(view);
}

template<typename T>
void MR::CMRDirector::AddView(const SmartPtr<T>& view)
{
	AddView(view.Get());
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

	pContext->Realize();

	if (!pContext->IsRealized())
	{
		m_bDone = true;
		return;
	}

	m_spView->SetStartTick(CMRTimer::Instance()->GetStartTick());

}

bool MR::CMRDirector::Done() const
{
	return m_bDone;
}

void MR::CMRDirector::SetDone( bool bDone )
{
	m_bDone = bDone;
}

void MR::CMRDirector::SetRealizeOperation(const CMROperation* op)
{
	m_spRealizeOperation = const_cast<CMROperation*>(op);
}

CMROperation* MR::CMRDirector::GetRealizeOperation() const
{
	return m_spRealizeOperation.Get();
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
		_DirectorInit();
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
	return CMRTimer::Instance()->DeltaS(GetStartTick(), CMRTimer::Instance()->Tick());
}

CMRFrameStamp* MR::CMRDirector::GetDirectorFrameStamp()
{
	return m_spView->GetFrameStamp();
}

void MR::CMRDirector::_DirectorConstructorInit()
{

}

void MR::CMRDirector::_DirectorInit()
{
	m_spView->Init();
}

