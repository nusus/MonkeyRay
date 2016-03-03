#ifndef CMRPrerequisites_h__
#define CMRPrerequisites_h__

#include "CMRConfig.h"
#include <string>
#ifdef MR_DEBUG_MODE

#endif

#include "CMRStdConfig.h"
#include "CMRContainerConfig.h"
#include "CMRMemoryAllocatorConfig.h"

namespace MR
{
#if MR_REAL_PRECISION == MR_SINGLE_PRECISION
	typedef float real;
#else
	typedef double real;
#endif

#if MR_REAL_STRING_TYPE == MR_USE_STRING
	typedef std::string string;
#else
	typedef std::wstring string;
#endif
}
#endif // CMRPrerequisites_h__
