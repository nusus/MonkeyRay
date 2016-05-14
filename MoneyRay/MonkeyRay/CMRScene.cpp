#include "CMRScene.h"


using namespace MR;

void MR::CMRScene::SetSceneData(CMRNode* pNode)
{
	m_spSceneData = pNode;

}

CMRNode* MR::CMRScene::GetSceneData()
{
	return m_spSceneData.Get();

}

CMRScene* MR::CMRScene::GetScene(CMRNode* pNode)
{
	return CMRSceneSingletonCache::Instance()->Get(pNode);

}

MR::CMRScene::CMRScene()
{
	CMRSceneSingletonCache::Instance()->Add(this);

}

MR::CMRScene::~CMRScene()
{
	CMRSceneSingletonCache::Instance()->Remove(this);

}

CMRScene* MR::CMRScene::GetOrCreateScene(CMRNode* pNode)
{
	if (!pNode)
	{
		return 0;
	}

	CMRScene* pScene = GetScene(pNode);
	if (!pScene)
	{
		pScene = new CMRScene;
		pScene->SetSceneData(pNode);
	}
	return pScene;
}

const CMRNode* MR::CMRScene::GetSceneData() const
{
	return m_spSceneData.Get();

}