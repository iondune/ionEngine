
#include "CSimpleMeshSceneObject.h"
#include "CRenderPass.h"


namespace ion
{
	namespace Scene
	{

		SSimpleMaterial::SSimpleMaterial()
		{
			LoadDefaults();
		}

		void SSimpleMaterial::LoadDefaults()
		{
			*Shininess = 1000.0f;
			*Ambient = SColorf(0.05f);
			*Diffuse = SColorf(0.9f);
			*Specular = SColorf(1.f);
		}

		CSimpleMeshSceneObject::~CSimpleMeshSceneObject()
		{}

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

			PipelineState->SetIndexBuffer(IndexBuffer = Mesh->CreateIndexBuffer(RenderPass->GetGraphicsAPI()));
			PipelineState->SetVertexBuffer(0, VertexBuffer = Mesh->CreateVertexBuffer(RenderPass->GetGraphicsAPI()));

			PipelineState->SetProgram(Shader);

			std::for_each(Textures.begin(), Textures.end(), [this](pair<string, SharedPtr<Graphics::ITexture>> const & Iterator)
			{
				PipelineState->SetTexture(Iterator.first, Iterator.second);
			});

			PipelineState->OfferUniform("uMaterial.AmbientColor", Material.Ambient);
			PipelineState->OfferUniform("uMaterial.DiffuseColor", Material.Diffuse);
			PipelineState->OfferUniform("uMaterial.SpecularColor", Material.Specular);
			PipelineState->OfferUniform("uMaterial.Shininess", Material.Shininess);

			RenderPass->PreparePipelineStateForRendering(PipelineState, this);
			Loaded = true;
		}

		void CSimpleMeshSceneObject::Draw(CRenderPass * RenderPass)
		{
			if (PipelineState)
			{
				RenderPass->SubmitPipelineStateForRendering(PipelineState, this);
			}
		}

		void CSimpleMeshSceneObject::SetMesh(CSimpleMesh * Mesh)
		{
			this->Mesh = Mesh;
			Loaded = false;
		}

		void CSimpleMeshSceneObject::SetShader(SharedPtr<Graphics::IShaderProgram> Shader)
		{
			this->Shader = Shader;
			Loaded = false;
		}

		void CSimpleMeshSceneObject::SetTexture(string const & Name, SharedPtr<Graphics::ITexture> Texture)
		{
			if (Texture)
			{
				Textures[Name] = Texture;
			}
			else
			{
				Textures.erase(Name);
			}
			Loaded = false;
		}

		SSimpleMaterial & CSimpleMeshSceneObject::GetMaterial()
		{
			return Material;
		}

		SSimpleMaterial const & CSimpleMeshSceneObject::GetMaterial() const
		{
			return Material;
		}

		void CSimpleMeshSceneObject::SetMaterial(SSimpleMaterial const & Material)
		{
			this->Material = Material;
		}

	}
}
