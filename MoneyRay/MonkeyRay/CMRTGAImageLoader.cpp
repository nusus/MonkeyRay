#include "CMRTGAImageLoader.h"

using namespace MR;

MR::CMRTGAImageLoader::CMRTGAImageLoader()
{

}

CMRImage::ImageEntity* MR::CMRTGAImageLoader::LoadImage(const string& strName)
{
	string name = strName;
	std::transform(name.begin(), name.end(), name.begin(), ::tolower);
	name = CMRConfig::Instance()->s_strTextureDir + name;
	SmartPtr<CMRImage::ImageEntity> retImageEntity = new CMRImage::ImageEntity;
	retImageEntity->width = 0;
	retImageEntity->height = 0;
	retImageEntity->format = GL_BGRA;
	retImageEntity->internal_format = GL_RGBA;
	retImageEntity->data_type = GL_UNSIGNED_BYTE;
	retImageEntity->data = NULL;

	TGAHeader tgaHeader;
	unsigned long lImageSize;
	short sDepth;

	void* pBits = NULL;

	FILE* pFile = fopen(name.c_str(), "rb");
	if (pFile == NULL)
	{
		CMR_STD_OUT << "Can not open TGA file: " << name << CMR_STD_ENDL;
		assert(false);
		return retImageEntity.Release();
	}
	size_t temp_int = sizeof(TGAHeader);
	fread(&tgaHeader, sizeof(TGAHeader), 1, pFile);

	retImageEntity->width = tgaHeader.width;
	retImageEntity->height = tgaHeader.height;
	sDepth = tgaHeader.depth / 8;

	if (sDepth != 1 && sDepth != 3 && sDepth != 4)
	{
		CMR_STD_OUT << "TGA file" << name << "image depth is not valid." << CMR_STD_ENDL;
		assert(false);
		return retImageEntity.Release();
	}

	lImageSize = retImageEntity->width * retImageEntity->height * sDepth;
	pBits = (void*)CMRObjectFactory<>::Malloc(lImageSize * sizeof(GLbyte));
	if (pBits == NULL)
	{
		CMR_STD_OUT << "malloc memory failed when load TGA file" << name << CMR_STD_ENDL;
		assert(false);
		return retImageEntity.Release();
	}
	if (fread(pBits, lImageSize, 1, pFile) != 1)
	{
		CMRObjectFactory<>::Free(pBits);
		return retImageEntity.Release();
	}

	switch (sDepth)
	{
	case 3:
		retImageEntity->format = GL_BGR;
		retImageEntity->internal_format = GL_RGB;
		break;
	case 4:
		retImageEntity->format = GL_BGRA;
		retImageEntity->internal_format = GL_RGBA;
		break;
	case 1:
		retImageEntity->format = GL_LUMINANCE;
		retImageEntity->internal_format = GL_LUMINANCE;
		break;
	default:
		break;
	}

	fclose(pFile);

	retImageEntity->data = pBits;
	if (pBits != NULL)
	{
		CMR_STD_OUT << "Load Image Success : " << name << CMR_STD_ENDL;
	}
	return retImageEntity.Release();
}
