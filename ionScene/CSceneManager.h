
#pragma once

#include "ICamera.h"
#include "CCamera.h"
#include "ISceneObject.h"
#include "CRenderPass.h"


namespace ion
{
	namespace Scene
	{

		class CSceneManager : public Singleton<CSceneManager>
		{

		public:

			virtual void Init(Graphics::IGraphicsAPI * GraphicsAPI);
			virtual void DrawAll();

			virtual void AddRenderPass(CRenderPass * RenderPass);

		protected:

			set<CRenderPass *> RenderPasses;
			Graphics::IGraphicsAPI * GraphicsAPI = nullptr;

		private:

			friend class Singleton<CSceneManager>;
			CSceneManager();

		};

	}
}
