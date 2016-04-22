#include "CConfig.h"
#if TEST2 == ON
#include "../MonkeyRay/CMRPrerequisites.h"
#include "../MonkeyRay/SmartPtr.h"
#include "../MonkeyRay/CMRObject.h"
#include "../MonkeyRay/CMRUserDataContainer.h"
#include "../MonkeyRay/WeakPtr.h"

using namespace MR;
int main(void)
{
	MR::WeakPtr<MR::CMRDefaultUserDataContainer> ptr = new CMRDefaultUserDataContainer();

	SmartPtr<CMRDefaultUserDataContainer> sptr;
	ptr.Lock(sptr);
	getchar();
}
#endif