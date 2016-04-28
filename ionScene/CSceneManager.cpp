
#include "CSceneManager.h"


namespace ion
{

	void CSceneManager::Init(CGraphicsAPI * GraphicsAPI)
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
		RenderPasses.push_back(RenderPass);
	}

	CSceneManager::CSceneManager()
	{}

}
