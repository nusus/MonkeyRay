#ifndef CMRTimer_h__
#define CMRTimer_h__
#include <stdint.h>

namespace MR
{
	typedef int64_t Timer_t;

	class CMRTimer
	{
	public:
		CMRTimer();
		~CMRTimer();
	public:
		static CMRTimer* Instance();

		Timer_t Tick() const;

		void SetStartTick();
		void SetStartTick(Timer_t t);
		Timer_t GetStartTick() const;

		/** Get elapsed time in seconds.*/
		double TimeS() const;

		/** Get elapsed time in milliseconds.*/
		double TimeM() const;

		/** Get elapsed time in microseconds.*/
		double TimeU() const;

		/** Get elapsed time in nanoseconds.*/
		double TimeN() const;

		/** Get the time in seconds between timer ticks t1 and t2.*/
		double DeltaS(Timer_t t1, Timer_t t2) const;

		/** Get the time in milliseconds between timer ticks t1 and t2.*/
		double DeltaM(Timer_t t1, Timer_t t2) const;

		/** Get the time in microseconds between timer ticks t1 and t2.*/
		double DeltaU(Timer_t t1, Timer_t t2) const;

		/** Get the time in nanoseconds between timer ticks t1 and t2.*/
		double DeltaN(Timer_t t1, Timer_t t2) const;

		/** Get the number of seconds per tick. */
		double GetSecondsPerTick() const;
	protected:
		Timer_t m_startTick;
		double m_secsPerTick;
	};


	class CMRElapsedTime
	{
	public:
		inline CMRElapsedTime(double* elapsedTime, CMRTimer* pTimer = 0);

		inline CMRElapsedTime(CMRTimer* timer);

		~CMRElapsedTime();
	public:
		void Reset();


		double ElapsedTime() const;

		double ElapsedTimeM() const;

		double ElapsedTimeU() const;

		void Finish();
	protected:
		void _Init(CMRTimer* pTimer);

	protected:
		double*		m_pTime;
		CMRTimer*	m_pTimer;
		Timer_t		m_startTick;
	private:
	};
}
#endif // CMRTimer_h__
