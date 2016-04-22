#ifndef CMRTexture_h__
#define CMRTexture_h__

#include "CMRImage.h"
#include "CMRTGAImageLoader.h"

namespace MR
{
	class CMRTexture
	{
	public:
		explicit CMRTexture(const std::string& name) :
			m_strFullPath( MR::CMRConfig::Instance()->s_strTextureDir + name),
			m_image(name)
		{
			_GetImageLoaderFromName(GetFileNameAux(name));
		}

		~CMRTexture()
		{
			if (m_imageLoader)
			{
				delete m_imageLoader;
				m_imageLoader = nullptr;
			}
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		bool LoadTexture()
		{
			m_image.LoadImage(*m_imageLoader);
			glGenTextures(1, &m_textureObject);
			glBindTexture(GL_TEXTURE_2D, m_textureObject);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_image.GetWidth(), m_image.GetHeight(), 0, m_image.GetFormat(), GL_UNSIGNED_BYTE, m_image.GetData());
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glBindTexture(GL_TEXTURE_2D, 0);
			return true;
		}

		void Bind(GLenum eTextureUnit)
		{
			glActiveTexture(eTextureUnit);
			glBindTexture(GL_TEXTURE_2D, m_textureObject);
		}


		GLuint GetTextureObject() const
		{
			return m_textureObject;
		}
	protected:
		void _GetImageLoaderFromName(const std::string& name)
		{
			m_imageLoader = new CMRTGAImageLoader();
		}
	protected:
		std::string m_strFullPath;
		CMRImage m_image;
		GLuint m_textureObject;
		CMRImageLoader* m_imageLoader;
	private:
	};
}
#endif // CMRTexture_h__
