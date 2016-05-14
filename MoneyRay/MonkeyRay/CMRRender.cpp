#include "CMRRender.h"
#include "CMRCamera.h"
#include "CMRStateGraph.h"
#include "CMRRenderStage.h"

using namespace MR;

MR::CMRRender::CMRRender(CMRCamera* pCamera) :
	m_wpCamera(pCamera)
{
	m_spStateGraph = new CMRStateGraph;
	m_spRenderStage = new CMRRenderStage;
}

void MR::CMRRender::Cull()
{
	m_spStateGraph->Reset();
	m_spRenderStage->Reset();

	m_spStateGraph->Init(m_wpCamera);
	m_spRenderStage->Init(m_spStateGraph.Get());
}

void MR::CMRRender::CullDraw()
{
	Cull();
	Draw();
}

void MR::CMRRender::Draw()
{
	m_spRenderStage->Draw();
}

