#include "CMRViewBase.h"

using namespace MR;

MR::CMRViewBase::CMRViewBase()
{
	m_spCamera = new CMRCamera;
	m_spCamera->SetView(this);

}

void MR::CMRViewBase::Take(CMRViewBase& view)
{
	m_spCamera = view.m_spCamera;
	if (m_spCamera.Valid())
	{
		m_spCamera->SetView(this);
	}
	view.m_spCamera = nullptr;

}

void MR::CMRViewBase::SetCamera(CMRCamera* camera)
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

CMRCamera* MR::CMRViewBase::GetCamera()
{
	return m_spCamera.Get();

}

void MR::CMRViewBase::SetFrameStamp(CMRFrameStamp* fs)
{
	m_spFrameStamp = fs;
}

CMRFrameStamp* MR::CMRViewBase::GetFrameStamp()
{
	return m_spFrameStamp.Get();
}

MR::CMRViewBase::~CMRViewBase()
{
	if (m_spCamera.Valid())
	{
		m_spCamera->SetView(nullptr);
	}
	m_spCamera = nullptr;

}

const CMRFrameStamp* MR::CMRViewBase::GetFrameStamp() const
{
	return m_spFrameStamp.Get();

}

const CMRCamera* MR::CMRViewBase::GetCamera() const
{
	return m_spCamera.Get();

}