
#include "CSceneManager.h"


namespace ion
{

	void CSceneManager::Init(CGraphicsAPI * GraphicsAPI)
	{}

	int CSceneManager::DrawAll()
	{
		SingletonPointer<CGraphicsAPI> GraphicsAPI;

		int numDraws = 0;

		int i = 0;
		for (Scene::CRenderPass * pass : RenderPasses)
		{
			string passName = pass->GetName();
			if (passName == "")
			{
				passName = String::Build("RenderPass%d", i);
			}

			GraphicsAPI->GetImplementation()->AnnotateBeginEvent(passName);
			pass->Load();
			numDraws += pass->Draw();
			GraphicsAPI->GetImplementation()->AnnotateEndEvent(passName);

			i ++;
		}

		return numDraws;
	}

	void CSceneManager::AddRenderPass(Scene::CRenderPass * RenderPass)
	{
		RenderPasses.push_back(RenderPass);
	}

	CSceneManager::CSceneManager()
	{}

}
