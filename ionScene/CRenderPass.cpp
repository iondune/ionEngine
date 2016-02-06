
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
		}

		void CRenderPass::SubmitPipelineStateForRendering(Graphics::IPipelineState * PipelineState)
		{
		}

	}
}
