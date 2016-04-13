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
	//TODO: MR::CMRTexture::CMRTexture is not implemented
	m_spImage = new CMRImage(name);
	m_strFullPath = CMRConfig::Instance()->s_strTextureDir + name;
}

MR::CMRTexture::~CMRTexture()
{
	//TODO: MR::CMRTexture::~CMRTexture is not implemented
	glBindTexture(m_target, 0);
}

bool MR::CMRTexture::LoadTexture()
{
	//TODO: MR::CMRTexture::LoadTexture is not implemented
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
	//TODO: MR::CMRTexture::Bind is not implemented
	glActiveTexture(eTextureUnit);
	glBindTexture(GetTarget(), m_textureObject);
}

const GLuint MR::CMRTexture::GetTextureObject() const
{
	//TODO: MR::CMRTexture::GetTextureObject is not implemented
	return m_textureObject;
}

void MR::CMRTexture::SetTarget(GLenum target)
{
	//TODO: MR::CMRTexture::SetTarget is not implemented
	m_target = target;
}

const GLenum MR::CMRTexture::GetTarget() const
{
	//TODO: MR::CMRTexture::GetTarget is not implemented
	return m_target;
}

void MR::CMRTexture::SetLevel(GLint level)
{
	//TODO: MR::CMRTexture::SetLevel is not implemented
	m_level = level;
}

const GLint MR::CMRTexture::GetLevel() const
{
	//TODO: MR::CMRTexture::GetLevel is not implemented
	return m_level;
}

void MR::CMRTexture::SetBorder(GLint border)
{
	//TODO: MR::CMRTexture::SetBorder is not implemented
	m_border = border;
}

const GLint MR::CMRTexture::GetBorder() const
{
	//TODO: MR::CMRTexture::GetBorder is not implemented
	return m_border;
}

const GLsizei MR::CMRTexture::GetWidth() const
{
	//TODO: MR::CMRTexture::GetWidth is not implemented
	return m_spImage->GetWidth();
}

const GLsizei MR::CMRTexture::GetHeight() const
{
	//TODO: MR::CMRTexture::GetHeight is not implemented
	return m_spImage->GetHeight();
}

const GLint MR::CMRTexture::GetInternalFormat() const
{
	//TODO: MR::CMRTexture::GetInternalFormat is not implemented
	return m_spImage->GetInternalFormat();
}

const GLenum MR::CMRTexture::GetFormat() const
{
	//TODO: MR::CMRTexture::GetFormat is not implemented
	return m_spImage->GetFormat();
}

const GLenum MR::CMRTexture::GetType() const
{
	//TODO: MR::CMRTexture::GetType is not implemented
	return m_spImage->GetDataType();
}

const void* MR::CMRTexture::GetData() const
{
	//TODO: MR::CMRTexture::GetData is not implemented
	return m_spImage->GetData();
}

void MR::CMRTexture::SetMagFilter(GLint magFilter)
{
	//TODO: MR::CMRTexture::SetMagFilter is not implemented
	m_magFilter = magFilter;
}

const GLint MR::CMRTexture::GetMagFilter() const
{
	//TODO: MR::CMRTexture::GetMagFilter is not implemented
	return m_magFilter;
}

void MR::CMRTexture::SetMinFilter(GLint minFilter)
{
	//TODO: MR::CMRTexture::SetMinFilter is not implemented
	m_minFilter = minFilter;
}

const GLint MR::CMRTexture::GetMinFilter() const
{
	//TODO: MR::CMRTexture::GetMinFilter is not implemented
	return m_minFilter;
}

void MR::CMRTexture::SetWrapS(GLint wrap_s)
{
	//TODO: MR::CMRTexture::SetWrapS is not implemented
	m_wrapS = wrap_s;
}

void MR::CMRTexture::SetWrapT(GLint wrap_t)
{
	//TODO: MR::CMRTexture::SetWrapT is not implemented
	m_wrapT = wrap_t;
}

const GLint MR::CMRTexture::GetWrapS() const
{
	//TODO: MR::CMRTexture::GetWrapS is not implemented
	return m_wrapS;
}

const GLint MR::CMRTexture::GetWrapT() const
{
	//TODO: MR::CMRTexture::GetWrapT is not implemented
	return m_wrapT;
}
