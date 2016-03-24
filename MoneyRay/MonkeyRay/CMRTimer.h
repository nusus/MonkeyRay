#ifndef CMRTimer_h__
#define CMRTimer_h__
#include <stdint.h>

namespace MR
{
	typedef int64_t Timer_t;

	class CMRTimer
	{
	public:
		static CMRTimer* Instance()
		{
			static CMRTimer s_timer;
			return &s_timer;
		}

		Timer_t Tick() const
		{
			//TODO:  is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

		double DeltaS(Timer_t startTick, Timer_t endTick)
		{
			//TODO:  is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

		Timer_t GetStartTick() const
		{
			//TODO:  is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}




	};
}
#endif // CMRTimer_h__
