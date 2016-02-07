
#include "CRenderPass.h"


namespace ion
{
	namespace Scene
	{

		string const & CRenderPass::GetName() const
		{
			return Name;
		}

		ICamera * CRenderPass::GetActiveCamera()
		{
			return ActiveCamera;
		}

		ICamera const * CRenderPass::GetActiveCamera() const
		{
			return ActiveCamera;
		}

		void CRenderPass::SetActiveCamera(ICamera * Camera)
		{
			ActiveCamera = Camera;
		}

		void CRenderPass::AddLight(ILight * Light)
		{
			Lights.insert(Light);
		}

		void CRenderPass::RemoveLight(ILight * Light)
		{
			Lights.erase(Light);
		}

		void CRenderPass::AddSceneObject(ISceneObject * SceneObject)
		{
			SceneObjects.insert(SceneObject);
		}

		void CRenderPass::RemoveSceneObject(ISceneObject * SceneObject)
		{
			SceneObjects.erase(SceneObject);
		}

		void CRenderPass::Load()
		{
			std::for_each(SceneObjects.begin(), SceneObjects.end(), [this](ISceneObject * SceneObject)
			{
				SceneObject->Load(this);
			});
		}

		void CRenderPass::Draw()
		{
			std::for_each(SceneObjects.begin(), SceneObjects.end(), [this](ISceneObject * SceneObject)
			{
				SceneObject->Draw(this);
			});
		}

		void CRenderPass::PreparePipelineStateForRendering(Graphics::IPipelineState * PipelineState)
		{
			PipelineState->OfferUniform("uViewMatrix", &uViewMatrix);
			PipelineState->OfferUniform("uProjectionMatrix", &uProjectionMatrix);
			PipelineState->OfferUniform("uCameraPosition", &uCameraPosition);

			PipelineState->Load();
		}

		void CRenderPass::SubmitPipelineStateForRendering(Graphics::IPipelineState * PipelineState)
		{
		}

	}
}
