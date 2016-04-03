
#include "CSimpleMeshSceneObject.h"
#include "CRenderPass.h"


namespace ion
{
	namespace Scene
	{

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
				PipelineState = RenderPass->GetGraphicsContext()->CreatePipelineState();
			}

			PipelineState->SetIndexBuffer(IndexBuffer = Mesh->CreateIndexBuffer());
			PipelineState->SetVertexBuffer(0, VertexBuffer = Mesh->CreateVertexBuffer());

			Material.LoadTextures();

			PipelineState->SetProgram(Shader);

			std::for_each(Textures.begin(), Textures.end(), [this](pair<string, SharedPointer<Graphics::ITexture>> const & Iterator)
			{
				PipelineState->SetTexture(Iterator.first, Iterator.second);
			});
			std::for_each(Uniforms.begin(), Uniforms.end(), [this](pair<string, SharedPointer<Graphics::IUniform>> const & Iterator)
			{
				PipelineState->SetUniform(Iterator.first, Iterator.second);
			});

			PipelineState->OfferUniform("uMaterial.AmbientColor", Material.Ambient);
			PipelineState->OfferUniform("uMaterial.DiffuseColor", Material.Diffuse);
			PipelineState->OfferUniform("uMaterial.SpecularColor", Material.Specular);
			PipelineState->OfferUniform("uMaterial.Shininess", Material.Shininess);
			if (Material.DiffuseTexture)
			{
				PipelineState->OfferTexture("uMaterial.DiffuseTexture", Material.DiffuseTexture);
			}

			for (auto Pair : DrawFeatures)
			{
				PipelineState->SetFeatureEnabled(Pair.first, Pair.second);
			}
			PipelineState->SetBlendMode(BlendMode);

			RenderPass->PreparePipelineStateForRendering(PipelineState, this);
			Loaded = true;
		}

		void CSimpleMeshSceneObject::Draw(CRenderPass * RenderPass)
		{
			if (PipelineState)
			{
				RenderPass->SubmitPipelineStateForRendering(PipelineState, this, 1, RenderCategory);
			}
		}

		void CSimpleMeshSceneObject::SetMesh(CSimpleMesh * Mesh)
		{
			this->Mesh = Mesh;
			this->Material = Mesh->Material;
			Loaded = false;
		}

		void CSimpleMeshSceneObject::SetShader(SharedPointer<Graphics::IShaderProgram> Shader)
		{
			this->Shader = Shader;
			Loaded = false;
		}

		void CSimpleMeshSceneObject::SetTexture(string const & Name, SharedPointer<Graphics::ITexture> Texture)
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

		void CSimpleMeshSceneObject::SetUniform(string const & Name, SharedPointer<Graphics::IUniform> Uniform)
		{
			if (Uniform)
			{
				Uniforms[Name] = Uniform;
			}
			else
			{
				Uniforms.erase(Name);
			}
			Loaded = false;
		}

		void CSimpleMeshSceneObject::SetFeatureEnabled(Graphics::EDrawFeature const Feature, bool const Enabled)
		{
			if (PipelineState)
			{
				PipelineState->SetFeatureEnabled(Feature, Enabled);
			}

			DrawFeatures[Feature] = Enabled;
		}

		void CSimpleMeshSceneObject::SetBlendMode(Graphics::EBlendMode const BlendMode)
		{
			if (PipelineState)
			{
				PipelineState->SetBlendMode(BlendMode);
			}

			this->BlendMode = BlendMode;
		}

		void CSimpleMeshSceneObject::SetRenderCategory(uint const Category)
		{
			this->RenderCategory = Category;
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
