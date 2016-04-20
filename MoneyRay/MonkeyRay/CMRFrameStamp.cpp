#include "CMRFrameStamp.h"

using namespace MR;

CMRFrameStamp& MR::CMRFrameStamp::operator=(const CMRFrameStamp& fs)
{
	if (this == &fs) return *this;

	m_uiFrameNumber = fs.m_uiFrameNumber;
	m_referenceTime = fs.m_referenceTime;
	m_simulationTime = fs.m_simulationTime;

	tm_sec = fs.tm_sec;            /* Seconds.    [0-60] (1 leap second) */
	tm_min = fs.tm_min;            /* Minutes.    [0-59] */
	tm_hour = fs.tm_hour;            /* Hours.    [0-23] */
	tm_mday = fs.tm_mday;            /* Day.        [1-31] */
	tm_mon = fs.tm_mon;            /* Month.    [0-11] */
	tm_year = fs.tm_year;            /* Year    - 1900.  */
	tm_wday = fs.tm_wday;            /* Day of week.    [0-6] */
	tm_yday = fs.tm_yday;            /* Days in year.[0-365]    */
	tm_isdst = fs.tm_isdst;            /* DST.        [-1/0/1]*/

	return *this;
}

MR::CMRFrameStamp::CMRFrameStamp(const CMRFrameStamp& fs)
{
	m_uiFrameNumber = fs.m_uiFrameNumber;
	m_referenceTime = fs.m_referenceTime;
	m_simulationTime = fs.m_simulationTime;

	tm_sec = fs.tm_sec;            /* Seconds.    [0-60] (1 leap second) */
	tm_min = fs.tm_min;            /* Minutes.    [0-59] */
	tm_hour = fs.tm_hour;            /* Hours.    [0-23] */
	tm_mday = fs.tm_mday;            /* Day.        [1-31] */
	tm_mon = fs.tm_mon;            /* Month.    [0-11] */
	tm_year = fs.tm_year;            /* Year    - 1900.  */
	tm_wday = fs.tm_wday;            /* Day of week.    [0-6] */
	tm_yday = fs.tm_yday;            /* Days in year.[0-365]    */
	tm_isdst = fs.tm_isdst;            /* DST.        [-1/0/1]*/
}

MR::CMRFrameStamp::CMRFrameStamp()
{
	m_uiFrameNumber = 0;
	m_referenceTime = 0;
	m_simulationTime = 0;

	tm_sec = 0;            /* Seconds.        [0-60] (1 leap second) */
	tm_min = 0;            /* Minutes.        [0-59] */
	tm_hour = 0;           /* Hours.          [0-23] */
	tm_mday = 0;           /* Day.            [1-31] */
	tm_mon = 0;            /* Month.          [0-11] */
	tm_year = 0;           /* Year            - 1900.  */
	tm_wday = 0;           /* Day of week.    [0-6] */
	tm_yday = 0;           /* Days in year.   [0-365]    */
	tm_isdst = 0;           /* DST.           [-1/0/1]*/
}

void MR::CMRFrameStamp::SetCalendarTime(const tm& ct)
{
	tm_sec = ct.tm_sec;            /* Seconds.    [0-60] (1 leap second) */
	tm_min = ct.tm_min;            /* Minutes.    [0-59] */
	tm_hour = ct.tm_hour;            /* Hours.    [0-23] */
	tm_mday = ct.tm_mday;            /* Day.        [1-31] */
	tm_mon = ct.tm_mon;            /* Month.    [0-11] */
	tm_year = ct.tm_year;            /* Year    - 1900.  */
	tm_wday = ct.tm_wday;            /* Day of week.    [0-6] */
	tm_yday = ct.tm_yday;            /* Days in year.[0-365]    */
	tm_isdst = ct.tm_isdst;            /* DST.        [-1/0/1]*/
}

void MR::CMRFrameStamp::GetCalendarTime(tm& ct) const
{
	ct.tm_sec = tm_sec;            /* Seconds.    [0-60] (1 leap second) */
	ct.tm_min = tm_min;            /* Minutes.    [0-59] */
	ct.tm_hour = tm_hour;            /* Hours.    [0-23] */
	ct.tm_mday = tm_mday;            /* Day.        [1-31] */
	ct.tm_mon = tm_mon;            /* Month.    [0-11] */
	ct.tm_year = tm_year;            /* Year    - 1900.  */
	ct.tm_wday = tm_wday;            /* Day of week.    [0-6] */
	ct.tm_yday = tm_yday;            /* Days in year.[0-365]    */
	ct.tm_isdst = tm_isdst;            /* DST.        [-1/0/1]*/
}

void MR::CMRFrameStamp::SetFrameNumber(unsigned int frameNumber)
{
	m_uiFrameNumber = frameNumber;
}

unsigned int MR::CMRFrameStamp::GetFrameNumber() const
{
	return m_uiFrameNumber;
}

double MR::CMRFrameStamp::GetReferenceTime() const
{
	return m_referenceTime;
}

void MR::CMRFrameStamp::SetReferenceTime(double referenceTime)
{
	m_referenceTime = referenceTime;
}

void MR::CMRFrameStamp::SetSimulationTime(double param1)
{
	m_simulationTime = param1;
}

double MR::CMRFrameStamp::GetSimulationTime() const
{
	return m_simulationTime;
}
