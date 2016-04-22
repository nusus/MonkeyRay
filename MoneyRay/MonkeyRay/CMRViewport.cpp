#include "CMRViewport.h"
#include "vmath.h"

using namespace MR;

CMRViewport& MR::CMRViewport::operator=(const CMRViewport& vp)
{
	if (&vp == this)
	{
		return *this;
	}
	m_x = vp.m_x;
	m_y = vp.m_y;
	m_width = vp.m_width;
	m_height = vp.m_height;
	return *this;
}

MR::CMRViewport::CMRViewport(const CMRViewport& vp) :m_x(vp.m_x),
m_y(vp.m_y),
m_width(vp.m_width),
m_height(vp.m_height)
{

}

MR::CMRViewport::CMRViewport() :m_x(0),
m_y(0),
m_width(640),
m_height(480)
{

}

MR::CMRViewport::CMRViewport(value_type x, value_type y, value_type width, value_type height) :m_x(x),
m_y(y),
m_width(width),
m_height(height)
{

}

void MR::CMRViewport::SetViewport(value_type x, value_type y, value_type width, value_type height)
{
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
}

void MR::CMRViewport::SetX(value_type x)
{
	m_x = x;
}

CMRViewport::value_type MR::CMRViewport::GetX() const
{
	return m_x;
}

void MR::CMRViewport::SetY(value_type y)
{
	m_y = y;
}

CMRViewport::value_type MR::CMRViewport::GetY() const
{
	return m_y;
}

void MR::CMRViewport::SetWidth(value_type width)
{
	m_width = width;
}

CMRViewport::value_type MR::CMRViewport::GetWidth() const
{
	return m_width;
}

void MR::CMRViewport::SetHeight(value_type height)
{
	m_height = height;
}

::CMRViewport::value_type MR::CMRViewport::GetHeight() const
{
	return m_height;
}

bool MR::CMRViewport::IsValid() const
{
	return m_width > 0 && m_height > 0;
}

double MR::CMRViewport::AspectRatio() const
{
	if (m_height != 0)
	{
		return m_width / m_height;
	}
	else
	{
		return 1.0f;
	}
}

const vmath::mat4 MR::CMRViewport::ComputeWindowMatrix() const
{
	vmath::mat4 ret = vmath::translate(1.0f, 1.0f, 1.0f);
	vmath::mat4 scale = vmath::scale(0.5f * (float)GetWidth(), 0.5f * (float)GetHeight(), 0.5f);
	vmath::mat4 translate = vmath::translate((float)GetX(), (float)GetY(), 0.0f);
	return  ret * scale * translate;
}

void MR::CMRViewport::Apply(CMRObject& state) const
{
	glViewport(
		static_cast<GLint>(m_x),
		static_cast<GLint>(m_y),
		static_cast<GLsizei>(m_width),
		static_cast<GLsizei>(m_height)
	);
}

MR::CMRViewport::~CMRViewport()
{

}
