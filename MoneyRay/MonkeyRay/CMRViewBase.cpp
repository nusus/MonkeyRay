#include "CMRViewBase.h"

using namespace MR;

MR::CMRViewBase::CMRViewBase()
{
	SetLightingMode(LightMode::HEADLIGHT);
	m_spCamera = new CMRCamera;
	m_spCamera->SetView(this);


}

void MR::CMRViewBase::Take(CMRViewBase& view)
{
	//TODO: MR::CMRViewBase::Take is not implemented

}

void MR::CMRViewBase::SetLightingMode(LightMode lightingMode)
{
	//TODO: MR::CMRViewBase::SetLightingMode is not implemented

}

MR::CMRViewBase::LightMode MR::CMRViewBase::GetLightingMode() const
{
	//TODO: MR::CMRViewBase::GetLightingMode is not implemented

}

void MR::CMRViewBase::SetLight(CMRLight* light)
{
	//TODO: MR::CMRViewBase::SetLight is not implemented

}

CMRLight* MR::CMRViewBase::GetLight()
{
	//TODO: MR::CMRViewBase::GetLight is not implemented

}

void MR::CMRViewBase::SetCamera(CMRCamera* camera)
{
	//TODO: MR::CMRViewBase::SetCamera is not implemented

}

CMRCamera* MR::CMRViewBase::GetCamera()
{
	//TODO: MR::CMRViewBase::GetCamera is not implemented

}

void MR::CMRViewBase::SetFrameStamp(CMRFrameStamp* fs)
{
	//TODO: MR::CMRViewBase::SetFrameStamp is not implemented

}

CMRFrameStamp* MR::CMRViewBase::GetFrameStamp()
{
	//TODO: MR::CMRViewBase::GetFrameStamp is not implemented

}

MR::CMRViewBase::~CMRViewBase()
{
	//TODO: MR::CMRViewBase::~CMRViewBase is not implemented

}

const CMRFrameStamp* MR::CMRViewBase::GetFrameStamp() const
{
	//TODO: MR::CMRViewBase::GetFrameStamp is not implemented

}

const CMRCamera* MR::CMRViewBase::GetCamera() const
{
	//TODO: MR::CMRViewBase::GetCamera is not implemented

}

const CMRLight* MR::CMRViewBase::GetLight() const
{
	//TODO: MR::CMRViewBase::GetLight is not implemented

}

MR::CMRViewBase::CMRViewBase(const CMRViewBase& vb, const CMRCopyPolicy& policy /*= CMRCopyPolicy::SHALLOW_COPY*/)
{
	//TODO: MR::CMRViewBase::CMRViewBase is not implemented

}
