
#pragma once

#include "ICamera.h"
#include "CCamera.h"
#include "ISceneObject.h"
#include "CRenderPass.h"


namespace ion
{

	class CSceneManager : public Singleton<CSceneManager>
	{

	public:

		virtual void Init(CGraphicsAPI * GraphicsAPI);
		virtual void DrawAll();

		virtual void AddRenderPass(Scene::CRenderPass * RenderPass);

	protected:

		set<Scene::CRenderPass *> RenderPasses;

	private:

		friend class Singleton<CSceneManager>;
		CSceneManager();

	};

}
