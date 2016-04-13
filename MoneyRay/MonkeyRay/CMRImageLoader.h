#ifndef CMRImageLoader_h__
#define CMRImageLoader_h__

#include "CMRPrerequisites.h"
#include "CMRImage.h"
#include "CMRRef.h"
namespace MR
{
	class CMRImageLoader : public CMRRef
	{
	public:
		virtual CMRImage::ImageEntity* LoadImage(const string& name) = 0;
	};

	CMRImageLoader* GetImageLoader(const string& strName);
}
#endif // CMRImageLoader_h__