
#include "CSimpleMeshSceneObject.h"
#include "CRenderPass.h"


namespace ion
{
	namespace Scene
	{

		void CSimpleMeshSceneObject::Load(CRenderPass * RenderPass)
		{
			if (! Mesh || ! Shader)
			{
				return;
			}

			if (! PipelineState)
			{
				PipelineState = RenderPass->GetGraphicsAPI()->CreatePipelineState();
			}

			PipelineState->SetIndexBuffer(Mesh->CreateIndexBuffer(RenderPass->GetGraphicsAPI()));
			PipelineState->SetVertexBuffer(Mesh->CreateVertexBuffer(RenderPass->GetGraphicsAPI()));
			PipelineState->SetProgram(Shader);

			Loaded = true;
			RenderPass->PreparePipelineStateForRendering(PipelineState, this);
		}

		void CSimpleMeshSceneObject::Draw(CRenderPass * RenderPass)
		{
			RenderPass->SubmitPipelineStateForRendering(PipelineState, this);
		}

		void CSimpleMeshSceneObject::SetMesh(CSimpleMesh * Mesh)
		{
			this->Mesh = Mesh;
		}

		void CSimpleMeshSceneObject::SetShader(Graphics::IShaderProgram * Shader)
		{
			this->Shader = Shader;
		}

	}
}
