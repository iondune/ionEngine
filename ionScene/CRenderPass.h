
#pragma once

#include "ICamera.h"
#include "ISceneObject.h"


namespace ion
{
	namespace Scene
	{

		class CRenderPass
		{

		public:

			virtual string const & GetName() const;

			virtual ICamera * GetActiveCamera();
			virtual ICamera const * GetActiveCamera() const;
			virtual void SetActiveCamera(ICamera * Camera);

			virtual void AddSceneObject(ISceneObject * SceneObject);
			virtual void RemoveSceneObject(ISceneObject * SceneObject);

			virtual void Load();
			virtual void Draw();

			virtual void PreparePipelineStateForRendering(Graphics::IPipelineState * PipelineState);
			virtual void SubmitPipelineStateForRendering(Graphics::IPipelineState * PipelineState);

		protected:

			ICamera * ActiveCamera = nullptr;
			set<ISceneObject *> SceneObjects;
			map<string, Graphics::IUniform *> Uniforms;
			string Name;

		};

	}
}
