
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

			std::for_each(Textures.begin(), Textures.end(), [this](pair<string, Graphics::ITexture *> const & Iterator)
			{
				PipelineState->SetTexture(Iterator.first, Iterator.second);
			});
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

		void CSimpleMeshSceneObject::SetTexture(string const & Name, Graphics::ITexture * Texture)
		{
			if (Texture)
			{
				Textures[Name] = Texture;
			}
			else
			{
				Textures.erase(Name);
			}
		}

	}
}
