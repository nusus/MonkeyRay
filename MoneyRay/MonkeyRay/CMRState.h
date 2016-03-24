#ifndef CMRState_h__
#define CMRState_h__
#include "CMRRef.h"
namespace MR
{
	class CMRState : public CMRRef
	{
	public:



		void SetMaxTexturePoolSize(unsigned int maxBufferObjectPoolSize)
		{
			//TODO: CMRState is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

		void SetMaxBufferObjectPoolSize(unsigned int maxBufferObjectPoolSize)
		{
			//TODO: CMRState is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}


	};
}
#endif // CMRState_h__
