#include "CMREvent.h"

MR::CMREvent::CMREvent():
 m_handled(false),
 m_time(0.0)
{}

MR::CMREvent::CMREvent(const CMREvent & rhs, const MR::CMRCopyPolicy & copyop):
	MR::CMRObject(rhs, copyop),
	m_handled(rhs.m_handled),
	m_time(rhs.m_time)
{}
