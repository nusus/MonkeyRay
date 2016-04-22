#ifndef CMRTGAImageLoader_h__
#define CMRTGAImageLoader_h__

#include "CGlobalInclude.h"
#include "CMRImageLoader.h"


namespace MR
{
	class CMRTGAImageLoader : public CMRImageLoader
	{
	public:
#pragma pack(push, 1)
		struct TGAHeader {
			int8_t id_len;
			int8_t map_t;
			int8_t img_t;
			int16_t map_first;
			int16_t map_len;
			int8_t map_entry;
			int16_t x;
			int16_t y;
			int16_t width;
			int16_t height;
			int8_t depth;
			int8_t alpha;
		};
#pragma pack(pop)
	public:
		CMRTGAImageLoader() :
			CMRImageLoader(std::string("tga"))
		{

		}

		virtual ImageEntity LoadImage(const std::string& name) override
		{
			ImageEntity retImageEntity;
			retImageEntity.width = 0;
			retImageEntity.height = 0;
			retImageEntity.format = GL_BGRA;
			retImageEntity.components = GL_RGBA;
			retImageEntity.data = NULL;

			const std::string strFileName = GetFileNameAux(name);
			if (!_ValidSuffixName(strFileName))
			{
				std::cout << strFileName <<" is not a valid name" << std::endl;
				return retImageEntity;
			}

			TGAHeader tgaHeader;
			unsigned long lImageSize;
			short sDepth;

			void* pBits = NULL;

			FILE* pFile = fopen(name.c_str(), "rb");
			if (pFile == NULL)
			{
				std::cout << "Can not open TGA file" << name << std::endl;
				return retImageEntity;
			}
			std::size_t temp_int = sizeof(TGAHeader);
			fread(&tgaHeader, sizeof(TGAHeader), 1, pFile);

			retImageEntity.width = tgaHeader.width;
			retImageEntity.height = tgaHeader.height;
			sDepth = tgaHeader.depth / 8;

			if (sDepth != 1 && sDepth != 3 && sDepth!= 4)
			{
				std::cout << "TGA file" << name << "image depth is not valid." << std::endl;
				return retImageEntity;
			}

			lImageSize = retImageEntity.width * retImageEntity.height * sDepth;
			pBits = (void*)malloc(lImageSize * sizeof(GLbyte));
			if (pBits == NULL)
			{
				std::cout << "malloc memory failed when load TGA file" << name << std::endl;
				return retImageEntity;
			}
			if (fread(pBits, lImageSize, 1, pFile) != 1)
			{
				free(pBits);
				return retImageEntity;
			}

			switch (sDepth)
			{
			case 3:
				retImageEntity.format = GL_BGR;
				retImageEntity.components = GL_RGB;
				break;
			case 4:
				retImageEntity.format = GL_BGRA;
				retImageEntity.components = GL_RGBA;
				break;
			case 1:
				retImageEntity.format = GL_LUMINANCE;
				retImageEntity.components = GL_LUMINANCE;
				break;
			default:
				break;
			}

			fclose(pFile);

			retImageEntity.data = pBits;
			if (pBits != NULL)
			{
				std::cout << "Load Image Success : " << name << std::endl;
			}
			return retImageEntity;
		}

	protected:
		bool _ValidSuffixName(const std::string& strName)
		{
			if (strName.empty() || strName.size() == 0)
			{
				return false;
			}
			std::size_t found = strName.find_first_of('.');
			if (found == std::string::npos)
			{
				return false;
			}
			std::string substrName = strName.substr(found + 1, strName.size() - found);
			if ( _stricmp(substrName.c_str(), m_strSuffixName.c_str()) == 0)
			{
				return true;
			}
			return false;
		}
	};
}
#endif // CMRTGAImageLoader_h__
