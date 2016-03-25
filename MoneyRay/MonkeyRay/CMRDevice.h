#ifndef CMRDevice_h__
#define CMRDevice_h__
#include "CMRObject.h"
namespace MR
{
	class CMRDevice : public CMRObject
	{
	public:
		enum {
			UNKNOWN = 0,
			RECEIVE_EVENTS = 1,
			SEND_EVENTS = 2
		};

		CMRDevice();
		CMRDevice(const CMRDevice& de, const CMRCopyPolicy& copyop);
		META_OBJECT(MonkeyRay, CMRDevice);

	};
}
#endif // CMRDevice_h__
