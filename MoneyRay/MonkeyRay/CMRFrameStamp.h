#ifndef CMRFrameStamp_h__
#define CMRFrameStamp_h__
#include "CMRRef.h"
namespace MR
{
	class CMRFrameStamp : public CMRRef
	{
	public:
		CMRFrameStamp();

		CMRFrameStamp(const CMRFrameStamp& fs);

		CMRFrameStamp& operator=(const CMRFrameStamp& fs);
	public:
		void SetCalendarTime(const tm& ct);

		void GetCalendarTime(tm& ct) const;
		void SetFrameNumber(unsigned int frameNumber);
		unsigned int GetFrameNumber() const;

		double GetReferenceTime() const;

		void SetReferenceTime(double referenceTime);	

		void SetSimulationTime(double param1);

		double GetSimulationTime() const;

	protected:
		unsigned int m_uiFrameNumber;
		double m_referenceTime;
		double m_simulationTime;

		int tm_sec;            /* Seconds.        [0-60] (1 leap second) */
		int tm_min;            /* Minutes.        [0-59] */
		int tm_hour;           /* Hours.          [0-23] */
		int tm_mday;           /* Day.            [1-31] */
		int tm_mon;            /* Month.          [0-11] */
		int tm_year;           /* Year            - 1900.  */
		int tm_wday;           /* Day of week.    [0-6] */
		int tm_yday;           /* Days in year.   [0-365]    */
		int tm_isdst;           /* DST.           [-1/0/1]*/
	};
}
#endif // CMRFrameStamp_h__
