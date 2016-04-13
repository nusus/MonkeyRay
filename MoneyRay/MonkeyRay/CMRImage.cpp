#include "CMRImage.h"
#include "CMRImagePager.h"

using namespace MR;

MR::CMRImage::CMRImage(const string& strName) :
	m_bLoaded(false)
{
	m_strFullPath = (CMRConfig::Instance())->s_strTextureDir + strName;
}

const GLsizei MR::CMRImage::GetWidth()
{
	if (!m_bLoaded)
	{
		LoadImage();
	}
	return m_spImageEntity->width;
}

const GLsizei MR::CMRImage::GetHeight()
{
	if (!m_bLoaded)
	{
		LoadImage();
	}
	return m_spImageEntity->height;
}

const void* MR::CMRImage::GetData()
{
	if (!m_bLoaded)
	{
		LoadImage();
	}
	return m_spImageEntity->data;
}

GLenum MR::CMRImage::GetInternalFormat()
{
	if (!m_bLoaded)
	{
		LoadImage();
	}
	return m_spImageEntity->internal_format;
}

GLenum MR::CMRImage::GetDataType()
{
	if (!m_bLoaded)
	{
		LoadImage();
	}
	return m_spImageEntity->data_type;
}

void MR::CMRImage::LoadImage()
{

	m_spImageEntity = CMRImagePager::Instance()->GetImageEntity(CMRFile::GetFileNameAux(m_strFullPath));
	if (m_spImageEntity.Valid() && m_spImageEntity->data != nullptr)
	{
		m_bLoaded = true;
	}
}

GLenum MR::CMRImage::GetFormat()
{
	if (!m_bLoaded)
	{
		LoadImage();
	}
	return m_spImageEntity->format;
}

MR::CMRImage::ImageEntity::~ImageEntity()
{
	if (data)
	{
		CMRObjectFactory<>::Free(data);
		data = nullptr;
	}
}
