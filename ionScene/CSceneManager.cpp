
#include "CSceneManager.h"


namespace ion
{
	namespace Scene
	{

		void CSceneManager::DrawAll()
		{
			std::for_each(RenderPasses.begin(), RenderPasses.end(), [](CRenderPass * RenderPass)
			{
				RenderPass->Load();
				RenderPass->Draw();
			});
		}

		void CSceneManager::AddRenderPass(CRenderPass * RenderPass)
		{
			RenderPasses.insert(RenderPass);
		}

		CSceneManager::CSceneManager()
		{}

	}
}
