#ifndef CMRFrameStamp_h__
#define CMRFrameStamp_h__

namespace MR
{
	class CMRFrameStamp
	{
	public:
		unsigned int GetFrameNumber() const
		{
			return m_uiFrameNumber;
		}

		double GetReferenceTime()
		{
			//TODO: CMRFrameStamp is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

		void SetFrameNumber(double refTime)
		{
			//TODO:  is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

		void SetSimulationTime(double param1)
		{
			//TODO:  is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}




	protected:
		unsigned int m_uiFrameNumber;
	private:
	};
}
#endif // CMRFrameStamp_h__
