#ifndef CMRCallback_h__
#define CMRCallback_h__

#include "CMRObject.h"

namespace MR
{
	class CMRCallback : public CMRObject
	{
	public:

		void AddNestedCallback(CMRCallback* pc)
		{
			//TODO:  is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

		CMRCallback* GetNestedCallback()
		{
			//TODO: CMRCallback is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

		void SetNestedCallback(CMRCallback* param1)
		{
			//TODO: CMRCallback is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

		void SetUpdateCallback(CMRCallback* newUpdateCallback)
		{
			//TODO: CMRCallback is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

		void RemoveNestedCallback(CMRCallback* pUC)
		{
			//TODO: CMRCallback is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}





	};
}
#endif // CMRCallback_h__
