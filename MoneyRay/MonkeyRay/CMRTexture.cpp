#include "CMRTexture.h"

using namespace MR;


MR::CMRTexture::CMRTexture(const std::string& name) :
	m_target(GL_TEXTURE_2D),
	m_level(0),
	m_border(0),
	m_magFilter(GL_LINEAR),
	m_minFilter(GL_LINEAR),
	m_wrapS(GL_REPEAT),
	m_wrapT(GL_REPEAT)
{
	m_spImage = new CMRImage(name);
	m_strFullPath = CMRConfig::Instance()->s_strTextureDir + name;
}

MR::CMRTexture::~CMRTexture()
{
	glBindTexture(m_target, 0);
}

bool MR::CMRTexture::LoadTexture()
{
	m_spImage->LoadImage();
	glGenTextures(1, &m_textureObject);
	glBindTexture(GetTarget(), m_textureObject);
	glTexImage2D(GetTarget(), GetLevel(), GetInternalFormat(), GetWidth(), GetHeight(), GetBorder(), GetFormat(), GetType(), GetData());
	glTexParameteri(GetTarget(), GL_TEXTURE_MIN_FILTER, GetMinFilter());
	glTexParameteri(GetTarget(), GL_TEXTURE_MAG_FILTER, GetMagFilter());
	glTexParameteri(GetTarget(), GL_TEXTURE_WRAP_S, GetWrapS());
	glTexParameteri(GetTarget(), GL_TEXTURE_WRAP_T, GetWrapT());
	glBindTexture(GetTarget(), 0);
	return true;
}

void MR::CMRTexture::Bind(GLenum eTextureUnit)
{
	glActiveTexture(eTextureUnit);
	glBindTexture(GetTarget(), m_textureObject);
}

const GLuint MR::CMRTexture::GetTextureObject() const
{
	return m_textureObject;
}

void MR::CMRTexture::SetTarget(GLenum target)
{
	m_target = target;
}

const GLenum MR::CMRTexture::GetTarget() const
{
	return m_target;
}

void MR::CMRTexture::SetLevel(GLint level)
{
	m_level = level;
}

const GLint MR::CMRTexture::GetLevel() const
{
	return m_level;
}

void MR::CMRTexture::SetBorder(GLint border)
{
	m_border = border;
}

const GLint MR::CMRTexture::GetBorder() const
{
	return m_border;
}

const GLsizei MR::CMRTexture::GetWidth() const
{
	return m_spImage->GetWidth();
}

const GLsizei MR::CMRTexture::GetHeight() const
{
	return m_spImage->GetHeight();
}

const GLint MR::CMRTexture::GetInternalFormat() const
{
	return m_spImage->GetInternalFormat();
}

const GLenum MR::CMRTexture::GetFormat() const
{
	return m_spImage->GetFormat();
}

const GLenum MR::CMRTexture::GetType() const
{
	return m_spImage->GetDataType();
}

const void* MR::CMRTexture::GetData() const
{
	return m_spImage->GetData();
}

void MR::CMRTexture::SetMagFilter(GLint magFilter)
{
	m_magFilter = magFilter;
}

const GLint MR::CMRTexture::GetMagFilter() const
{
	return m_magFilter;
}

void MR::CMRTexture::SetMinFilter(GLint minFilter)
{
	m_minFilter = minFilter;
}

const GLint MR::CMRTexture::GetMinFilter() const
{
	return m_minFilter;
}

void MR::CMRTexture::SetWrapS(GLint wrap_s)
{
	m_wrapS = wrap_s;
}

void MR::CMRTexture::SetWrapT(GLint wrap_t)
{
	m_wrapT = wrap_t;
}

const GLint MR::CMRTexture::GetWrapS() const
{
	return m_wrapS;
}

const GLint MR::CMRTexture::GetWrapT() const
{
	return m_wrapT;
}
