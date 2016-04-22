#ifndef CMRScene_h__
#define CMRScene_h__
#include "CMRRef.h"
#include "SmartPtr.h"
#include "CMRSingleton.h"
#include "CMRNode.h"
namespace MR 
{

	struct CMRSceneSingletonCache : TMRSingletonCache<CMRScene> 
	{
		value_type* Get(CMRNode* node);
	};

	class CMRScene : public CMRRef
	{
	public:
		void SetSceneData(CMRNode* pNode);
		CMRNode* GetSceneData();
		const CMRNode* GetSceneData() const;
		

		static CMRScene* GetScene(CMRNode* pNode);
	protected:
		CMRScene();
		virtual ~CMRScene();
		static CMRScene* GetOrCreateScene(CMRNode* pNode);

		friend class CMRView;

		SmartPtr<CMRNode> m_spSceneData;

	};
}
#endif // CMRScene_h__
