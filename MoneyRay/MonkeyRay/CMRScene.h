#ifndef CMRScene_h__
#define CMRScene_h__
#include "CMRRef.h"
#include "SmartPtr.h"
#include "CMRSingleton.h"
#include "CMRNode.h"
namespace MR 
{
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


	protected:
		static CMRScene* GetOrCreateScene(CMRNode* pNode);

		friend class CMRView;


	protected:
		SmartPtr<CMRNode> m_spSceneData;

	};

	struct CMRSceneSingletonCache : public TMRSingleton<CMRSceneSingletonCache> , public TMRSingletonCache<CMRScene> 
	{
	public:
		inline value_type* Get(CMRNode* node)
		{
			for (auto x : m_cache)
			{
				if (x && x->GetSceneData() == node)
				{
					return x;
				}
			}
			return 0;
		}
	};

	
}
#endif // CMRScene_h__
