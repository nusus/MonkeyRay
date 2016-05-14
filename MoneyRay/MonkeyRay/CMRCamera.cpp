#include "CMRCamera.h"
#include "CMRGraphicsContext.h"

using namespace MR;

const vmath::mat4& MR::CMRCamera::GetProjectionMatrix() const
{
	return m_matProjectionMatrix;
}

bool MR::CMRCamera::GetProjectionMatrixAsFrustum(double& left, double& right, double& bottom, double& top, double& zNear, double& zFar) const
{
	return m_matProjectionMatrix.GetProjectionMatrixAsFrustum(left, right, bottom, top, zNear, zFar);
}

bool MR::CMRCamera::GetProjectionMatrixAsPerspective(double& fovy, double& aspectRatio, double& zNear, double& zFar) const
{
	return m_matProjectionMatrix.GetProjectionMatrixAsPerspective(fovy, aspectRatio, zNear, zFar);
}

vmath::mat4& MR::CMRCamera::GetProjectionMatrix()
{
	return m_matProjectionMatrix;
}

void MR::CMRCamera::SetViewMatrix(const vmath::mat4& matrix)
{
	m_matViewMatrix = matrix;
}

vmath::mat4& MR::CMRCamera::GetViewMatrix()
{
	return m_matViewMatrix;
}

void MR::CMRCamera::SetViewMatrixAsLookAt(const vmath::vec3& eye, const vmath::vec3& center, const vmath::vec3& up)
{
	m_matViewMatrix = vmath::lookat(eye, center, up);
}

//this method is to be corrected.
void MR::CMRCamera::GetViewMatrixAsLookAt(vmath::vec3& eye, vmath::vec3& center, vmath::vec3& up, double lookDistance /*= 1.0*/) const
{
	m_matProjectionMatrix.GetViewMatrixAsLookAt(eye, center, up, lookDistance);
}

vmath::mat4 MR::CMRCamera::GetInverseViewMatrix() const
{
	return vmath::mat4();
}

const vmath::mat4& MR::CMRCamera::GetViewMatrix() const
{
	return m_matViewMatrix;

}

void MR::CMRCamera::SetGraphicsContext(CMRGraphicsContext* context)
{
	if (context)
	{
		m_spGraphicsContext = context;
	}

}

const CMRGraphicsContext* MR::CMRCamera::GetGraphicsContext() const
{
	return m_spGraphicsContext.Get();
}

CMRGraphicsContext* MR::CMRCamera::GetGraphicsContext()
{
	return m_spGraphicsContext.Get();
}

void MR::CMRCamera::SetRender(CMROperation* rc)
{
	m_spRender = rc;
}

const CMROperation* MR::CMRCamera::GetRender() const
{
	return m_spRender.Get();
}

MR::CMRCamera::~CMRCamera()
{

}

CMROperation* MR::CMRCamera::GetRender()
{
	return m_spRender.Get();
}

MR::CMRCamera::CMRCamera()
{

}

const CMRCamera* MR::CMRCamera::AsCamera() const
{
	return this;
}

CMRCamera* MR::CMRCamera::AsCamera()
{
	return this;
}

void MR::CMRCamera::SetView(CMRView* pView)
{
	m_pView = pView;
}

const CMRView* MR::CMRCamera::GetView() const
{
	return m_pView;
}

void MR::CMRCamera::SetViewport(CMRViewport* pViewport)
{
	m_spViewport = pViewport;
}

const CMRViewport* MR::CMRCamera::GetViewport() const
{
	return m_spViewport.Get();
}

void MR::CMRCamera::SetProjectionMatrix(const vmath::mat4& matrix)
{
	m_matProjectionMatrix = matrix;

}

void MR::CMRCamera::SetProjectionMatrixAsFrustum(double left, double right, double bottom, double top, double zNear, double zFar)
{
	m_matProjectionMatrix = vmath::frustum(left, right, bottom, top, zNear, zFar);

}

void MR::CMRCamera::SetProjectionMatrixAsPerspective(double fovy, double aspectRatio, double zNear, double zFar)
{
	m_matProjectionMatrix = vmath::perspective(fovy, aspectRatio, zNear, zFar);

}

CMRViewport* MR::CMRCamera::GetViewport()
{
	return m_spViewport.Get();

}

void MR::CMRCamera::SetViewport(int x, int y, int width, int height)
{
	if (m_spViewport.Valid())
	{
		m_spViewport->SetViewport(x, y, width, height);
	}
	else
	{
		m_spViewport = new CMRViewport(x, y, width, height);
	}

}

CMRView* MR::CMRCamera::GetView()
{
	return m_pView;
}
