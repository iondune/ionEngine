
#include "CRenderPass.h"


namespace ion
{
	namespace Scene
	{

		CRenderPass::CRenderPass(Graphics::IGraphicsAPI * GraphicsAPI)
		{
			this->GraphicsAPI = GraphicsAPI;
		}

		string const & CRenderPass::GetName() const
		{
			return Name;
		}

		Graphics::IGraphicsAPI * CRenderPass::GetGraphicsAPI()
		{
			return GraphicsAPI;
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
			if (ActiveCamera)
			{
				ActiveCamera->Update();

				uViewMatrix = ActiveCamera->GetViewMatrix();
				uProjectionMatrix = ActiveCamera->GetProjectionMatrix();
				uCameraPosition = ActiveCamera->GetPosition();
			}

			std::for_each(SceneObjects.begin(), SceneObjects.end(), [this](ISceneObject * SceneObject)
			{
				if (! SceneObject->IsLoaded())
				{
					SceneObject->Load(this);
				}
			});
		}

		void CRenderPass::Draw()
		{
			std::for_each(SceneObjects.begin(), SceneObjects.end(), [this](ISceneObject * SceneObject)
			{
				if (SceneObject->IsVisible())
				{
					SceneObject->Draw(this);
				}
			});
		}

		void CRenderPass::PreparePipelineStateForRendering(Graphics::IPipelineState * PipelineState, ISceneObject * SceneObject)
		{
			PipelineState->OfferUniform("uModelMatrix", &uModelMatrix);
			PipelineState->OfferUniform("uViewMatrix", &uViewMatrix);
			PipelineState->OfferUniform("uProjectionMatrix", &uProjectionMatrix);
			PipelineState->OfferUniform("uCameraPosition", &uCameraPosition);

			PipelineState->Load();
		}

		void CRenderPass::SubmitPipelineStateForRendering(Graphics::IPipelineState * PipelineState, ISceneObject * SceneObject)
		{
			uModelMatrix = SceneObject->GetTransformation();

			GraphicsAPI->Draw(PipelineState);
		}

	}
}
