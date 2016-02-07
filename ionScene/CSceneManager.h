
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

			virtual void DrawAll();

			void AddRenderPass(CRenderPass * RenderPass);

		protected:

			set<CRenderPass *> RenderPasses;

		private:

			friend class Singleton<CSceneManager>;
			CSceneManager();

		};

	}
}
