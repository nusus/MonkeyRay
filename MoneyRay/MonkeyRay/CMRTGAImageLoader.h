#ifndef CMRTGAImageLoader_h__
#define CMRTGAImageLoader_h__
#include "CMRImageLoader.h"
#include "CMRFile.h"
#include "CMRImage.h"
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
		CMRTGAImageLoader();

		virtual CMRImage::ImageEntity* LoadImage(const string& name) override;
	};
}
#endif // CMRTGAImageLoader_h__
