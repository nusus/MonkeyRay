#ifndef CMRImage_h__
#define CMRImage_h__
#include "CGlobalInclude.h"
#include "CMRImageLoader.h"
namespace MR
{
	class CMRImage
	{
	public:
		
	public:
		explicit CMRImage(const std::string& strName):
			m_bLoaded(false),
			m_strFullPath(MR::CMRConfig::Instance()->s_strTextureDir + strName)
		{
		}

		~CMRImage() 
		{
			FreeImage();
		}

		const std::size_t GetWidth()
		{
			assert(m_bLoaded);
			return m_imageEntity.width;
		}

		const std::size_t GetHeight()
		{
			assert(m_bLoaded);
			return m_imageEntity.height;
		}

		const void* GetData()
		{
			assert(m_bLoaded);
			return m_imageEntity.data;
		}

		void LoadImage(CMRImageLoader& loader)
		{
			m_imageEntity = loader.LoadImage(m_strFullPath);
			m_bLoaded = true;
		}

		GLenum GetFormat()
		{
			assert(m_bLoaded);
			return m_imageEntity.format;
		}

		void FreeImage()
		{
			if (m_imageEntity.data)
			{
				free(m_imageEntity.data);
				m_imageEntity.data = nullptr;
			}
		}
		
	protected:
		bool m_bLoaded;
		std::string m_strFullPath;
		ImageEntity m_imageEntity;
		
	private:
	};
}
#endif // CMRImage_h__
