#ifndef CMRImagePager_h__
#define CMRImagePager_h__
#include "CMRPrerequisites.h"
#include "CMRFrameStamp.h"
#include "CMRImage.h"
namespace MR
{
	class CMRImagePager
	{
	public:
		typedef unordered_map<string, SmartPtr<CMRImage::ImageEntity> > ImageCacheMap;
	public:
		static CMRImagePager* Instance();

		void SignalBeginFrame(CMRFrameStamp* pFrameStamp);

		CMRImage::ImageEntity* GetImageEntity(const string& strFileName);

	protected:
		ImageCacheMap m_map;
	private:

	};
}
#endif // CMRImagePager_h__
