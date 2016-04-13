#include "CMRImagePager.h"

using namespace MR;


CMRImagePager* MR::CMRImagePager::Instance()
{
	static CMRImagePager s_imagePager;
	return &s_imagePager;
}

void MR::CMRImagePager::SignalBeginFrame(CMRFrameStamp* pFrameStamp)
{
	//TODO: MR::CMRImagePager::SignalBeginFrame is not implemented

}

CMRImage::ImageEntity* MR::CMRImagePager::GetImageEntity(const string& strFileName)
{
	if (m_map.find(strFileName) != m_map.end() && m_map[strFileName].Valid())
	{
		return m_map[strFileName].Get();
	}
	else
	{
		m_map[strFileName] = GetImageLoader(strFileName)->LoadImage(strFileName);
		return m_map[strFileName].Release();
	}
}
