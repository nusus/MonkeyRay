#include "CMRView.h"
#include "CMRTimer.h"
#include "CMRScene.h"
#include "CMRRender.h"
using namespace MR;


Timer_t MR::CMRView::GetStartTick() const
{
	return m_startTick;
}

void MR::CMRView::SetCamera(CMRCamera* camera)
{
	if (m_spCamera.Valid())
	{
		m_spCamera->SetView(nullptr);
	}
	m_spCamera = camera;
	if (m_spCamera.Valid())
	{
		m_spCamera->SetView(this);
		m_spCamera->SetRender(_CreateRender(camera));
	}
}

CMRCamera* MR::CMRView::GetCamera()
{
	return m_spCamera.Get();
}

void MR::CMRView::SetFrameStamp(CMRFrameStamp* fs)
{
	m_spFrameStamp = fs;
}

const CMRCamera* MR::CMRView::GetCamera() const
{
	return m_spCamera.Get();
}

CMRFrameStamp* MR::CMRView::GetFrameStamp()
{
	return m_spFrameStamp.Get();
}

const CMRFrameStamp* MR::CMRView::GetFrameStamp() const
{
	return m_spFrameStamp.Get();
}

const CMRScene* MR::CMRView::GetScene() const
{
	return m_spScene.Get();
}

CMRScene* MR::CMRView::GetScene()
{
	return m_spScene.Get();
}

template<typename T>
void MR::CMRView::SetSceneData(const SmartPtr<T>& spScene)
{
	SetSceneData(spScene.Get());
}

void MR::CMRView::SetSceneData(CMRNode* pSceneData)
{
	if (pSceneData == m_spScene->GetSceneData())
	{
		return;
	}
	SmartPtr<CMRScene> spScene = CMRScene::GetScene(pSceneData);
	if (spScene.Valid())
	{
		m_spScene = spScene;
	}
	else
	{
		if (m_spScene->ReferenceCount() != 1)
		{
			m_spScene = new CMRScene;
		}
		else
		{

		}
		m_spScene->SetSceneData(pSceneData);
	}

	AssignSceneDataToCameras();

}

const CMRNode* MR::CMRView::GetSceneData() const
{
	return m_spScene.Valid() ? m_spScene->GetSceneData() : 0;
}

void MR::CMRView::Home()
{
	//TODO: MR::CMRView::Home is not implemented

}

void MR::CMRView::AssignSceneDataToCameras()
{
	CMRNode* pNode = m_spScene.Valid() ? m_spScene->GetSceneData() : 0;
	if (m_spCamera.Valid())
	{
		m_spCamera->RemoveChildren(0, m_spCamera->GetNumChildren());
		if (pNode)
		{
			m_spCamera->AddChild(pNode);
		}

	}

}

CMRNode* MR::CMRView::GetSceneData()
{
	return m_spScene.Valid() ? m_spScene->GetSceneData() : 0;
}


MR::CMRView::CMRView()
	:CMRGraphicsWindow(),
	m_startTick(0)
{
	Init();

}

CMRView* MR::CMRView::AsView()
{
	return this;
}

void MR::CMRView::SetDirector(CMRDirector* pDirector)
{
	m_pDirector = pDirector;
}

CMRDirector* MR::CMRView::GetDirector() const
{
	return m_pDirector;
}

void MR::CMRView::Take(CMRView& view)
{
	m_spCamera = view.m_spCamera;
	if (m_spCamera.Valid())
	{
		m_spCamera->SetView(this);
	}
	view.m_spCamera = nullptr;


	CMRView* pView = dynamic_cast<CMRView*>(&view);
	if (pView)
	{
		this->m_startTick = pView->m_startTick;
		m_spFrameStamp = pView->m_spFrameStamp;
		if (pView->GetSceneData())
		{
			m_spScene = pView->m_spScene;
		}

		pView->m_spFrameStamp = nullptr;
		pView->m_spScene = nullptr;
	}
	AssignSceneDataToCameras();

}

void MR::CMRView::SetStartTick(Timer_t startTick)
{
	m_startTick = startTick;
}

void MR::CMRView::Init()
{
	m_spCamera = new CMRCamera;
	m_spCamera->SetView(this);

	m_spFrameStamp = new CMRFrameStamp;
	m_spFrameStamp->SetFrameNumber(0);
	m_spFrameStamp->SetReferenceTime(0);
	m_spFrameStamp->SetSimulationTime(0);

	m_spScene = new CMRScene;

	GetCamera()->SetRender(_CreateRender(GetCamera()));

	if (m_spCamera.Valid())
	{
		m_spCamera->SetGraphicsContext(CMRGraphicsContext::Instance(GetFullScreen(), GetWindowName(), GetWidth(), GetHeight()));
		m_spCamera->SetViewport(GetScreenX(), GetScreenY(), GetWidth(), GetHeight());
	}
	else
	{
		m_spCamera = new CMRCamera;
		m_spCamera->SetGraphicsContext(CMRGraphicsContext::Instance(GetFullScreen(), GetWindowName(), GetWidth(), GetHeight()));
		m_spCamera->SetViewport(GetScreenX(), GetScreenY(), GetWidth(), GetHeight());
	}
}

MR::CMRView::CMRView(int x, int y, int width, int height, bool bFullScreen, string windowName)
	:CMRGraphicsWindow(x, y, width, height, bFullScreen, windowName),
	m_startTick(0)
{
	Init();
}

MR::CMRView::~CMRView()
{
	if (m_spCamera.Valid())
	{
		m_spCamera->SetView(nullptr);
	}
	m_spCamera = nullptr;
}

CMROperation* MR::CMRView::_CreateRender(CMRCamera* pCamera)
{
	CMRRender* pRender = new CMRRender(pCamera);
	return pRender;

}


