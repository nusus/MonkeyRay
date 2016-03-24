#ifndef CMRScene_h__
#define CMRScene_h__

#include "CMRDatabasePager.h"
#include "CMRImagePager.h"
namespace MR
{
	class CMRScene
	{
	public:

		CMRDatabasePager* GetDataBasePager() const;
		CMRImagePager* GetImagePager() const;

		CMRNode* GetSceneData()
		{
			//TODO: CMRScene is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

		void UpdateSceneData()
		{
			//TODO:  is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

		void UpdateSceneGraph()
		{
			//TODO:  is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}






	protected:
	private:
	};
}
#endif // CMRScene_h__
