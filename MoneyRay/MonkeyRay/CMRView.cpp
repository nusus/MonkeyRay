#include "CMRView.h"
#include "CMRTimer.h"
#include "CMRScene.h"
#include "CMRRender.h"
using namespace MR;


Timer_t MR::CMRView::GetStartTick() const
{
	return m_startTick;
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
	:CMRViewBase()
	,m_startTick(0)
{
	m_spFrameStamp = new CMRFrameStamp;
	m_spFrameStamp->SetFrameNumber(0);
	m_spFrameStamp->SetReferenceTime(0);
	m_spFrameStamp->SetSimulationTime(0);

	m_spScene = new CMRScene;

	GetCamera()->SetRender(_CreateRender(GetCamera()));

}

CMRView* MR::CMRView::AsView()
{
	return this;
}

CMRDirector* MR::CMRView::GetDirector() const
{
	return m_pDirector;
}

void MR::CMRView::Take(CMRView& view)
{
	CMRViewBase::Take(view);
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
}

MR::CMRView::~CMRView()
{

}

CMROperation* MR::CMRView::_CreateRender(CMRCamera* pCamera)
{
	CMRRender* pRender = new CMRRender(pCamera);
	return pRender;

}
