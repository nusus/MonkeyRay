#include "CMRCopyPolicy.h"

using namespace MR;

#define COPY_OP( TYPE, FLAG ) \
TYPE* CMRCopyPolicy::Copy (const TYPE* obj) const \
{ \
    if (obj && m_flags&FLAG) \
        return MR::Copy(obj, *this); \
    else \
        return const_cast<TYPE*>(obj); \
}

COPY_OP(CMRObject, DEEP_COPY_OBJECTS)

CMRRef* MR::CMRCopyPolicy::Copy(const CMRRef* ref) const
{
	return const_cast<CMRRef*>(ref);
}
