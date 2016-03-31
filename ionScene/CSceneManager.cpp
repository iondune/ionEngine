
#include "CSceneManager.h"


namespace ion
{

	void CSceneManager::Init()
	{}

	void CSceneManager::DrawAll()
	{
		std::for_each(RenderPasses.begin(), RenderPasses.end(), [](Scene::CRenderPass * RenderPass)
		{
			RenderPass->Load();
			RenderPass->Draw();
		});
	}

	void CSceneManager::AddRenderPass(Scene::CRenderPass * RenderPass)
	{
		RenderPasses.insert(RenderPass);
	}

	CSceneManager::CSceneManager()
	{}

}
