#include "CMRTimer.h"

#include <sys/types.h>
#include <fcntl.h>
#include <windows.h>
#include <WinBase.h>

using namespace MR;

MR::CMRTimer::CMRTimer()
{
	LARGE_INTEGER frequency;
	if (QueryPerformanceFrequency(&frequency))
	{
		m_secsPerTick = 1.0 / (double)frequency.QuadPart;
	}
	else
	{
		m_secsPerTick = 1.0;
	}
	SetStartTick();

}

MR::CMRTimer::~CMRTimer()
{

}

CMRTimer* MR::CMRTimer::Instance()
{
	static CMRTimer s_timer;
	return &s_timer;
}

MR::Timer_t MR::CMRTimer::Tick() const
{
	LARGE_INTEGER qpc;
	if (QueryPerformanceCounter(&qpc))
	{
		return qpc.QuadPart;
	}
	else
	{
		return 0;
	}
}

void MR::CMRTimer::SetStartTick(Timer_t t)
{
	m_startTick = t;
}

void MR::CMRTimer::SetStartTick()
{
	m_startTick = Tick();
}

MR::Timer_t MR::CMRTimer::GetStartTick() const
{
	return m_startTick;
}

double MR::CMRTimer::TimeS() const
{
	return DeltaS(m_startTick, Tick());
}

double MR::CMRTimer::TimeM() const
{
	return DeltaM(m_startTick, Tick());
}

double MR::CMRTimer::TimeU() const
{
	return DeltaU(m_startTick, Tick());
}

double MR::CMRTimer::TimeN() const
{
	return DeltaN(m_startTick, Tick());
}

double MR::CMRTimer::DeltaS(Timer_t t1, Timer_t t2) const
{
	return (double)(t2 - t1)*m_secsPerTick;
}

double MR::CMRTimer::DeltaM(Timer_t t1, Timer_t t2) const
{
	return DeltaS(t1, t2)*1e3;
}

double MR::CMRTimer::DeltaU(Timer_t t1, Timer_t t2) const
{
	return DeltaS(t1, t2)*1e6;
}

double MR::CMRTimer::DeltaN(Timer_t t1, Timer_t t2) const
{
	return DeltaS(t1, t2)*1e9;
}

double MR::CMRTimer::GetSecondsPerTick() const
{
	return m_secsPerTick;
}

MR::CMRElapsedTime::~CMRElapsedTime()
{
	Finish();
}

MR::CMRElapsedTime::CMRElapsedTime(CMRTimer* timer) :m_pTime(0)
{
	_Init(timer);
}

MR::CMRElapsedTime::CMRElapsedTime(double* elapsedTime, CMRTimer* pTimer /*= 0*/) :m_pTime(elapsedTime)
{
	_Init(pTimer);
}

void MR::CMRElapsedTime::Reset()
{
	m_startTick = m_pTimer->Tick();
}

double MR::CMRElapsedTime::ElapsedTime() const
{
	return m_pTimer->DeltaS(m_startTick, m_pTimer->Tick());
}

double MR::CMRElapsedTime::ElapsedTimeM() const
{
	return m_pTimer->DeltaM(m_startTick, m_pTimer->Tick());
}

double MR::CMRElapsedTime::ElapsedTimeU() const
{
	return m_pTimer->DeltaU(m_startTick, m_pTimer->Tick());
}

void MR::CMRElapsedTime::Finish()
{
	Timer_t endTick = m_pTimer->Tick();
	if (m_pTime)
	{
		*m_pTime += m_pTimer->DeltaS(m_startTick, endTick);
	}
	m_startTick = endTick;
}

void MR::CMRElapsedTime::_Init(CMRTimer* pTimer)
{
	if (pTimer)
	{
		m_pTimer = pTimer;
	}
	else
	{
		m_pTimer = CMRTimer::Instance();
	}
	m_startTick = m_pTimer->Tick();
}
