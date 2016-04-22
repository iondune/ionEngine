
#include "CSimpleSceneObject.h"
#include "CRenderPass.h"


namespace ion
{
	namespace Scene
	{

		CSimpleSceneObject::~CSimpleSceneObject()
		{}

		void CSimpleSceneObject::Load(CRenderPass * RenderPass)
		{
			if (! IndexBuffer || ! VertexBuffer || ! Shader)
			{
				return;
			}

			SharedPointer<Graphics::IPipelineState> PipelineState;
			if (! TryMapAccess(PipelineStates, RenderPass, PipelineState))
			{
				PipelineStates[RenderPass] = PipelineState = RenderPass->GetGraphicsContext()->CreatePipelineState();
			}

			PipelineState->SetIndexBuffer(IndexBuffer);
			PipelineState->SetVertexBuffer(0, VertexBuffer);

			Material.LoadTextures();

			PipelineState->SetProgram(Shader);

			std::for_each(Textures.begin(), Textures.end(), [this, PipelineState](pair<string, SharedPointer<Graphics::ITexture>> const & Iterator)
			{
				PipelineState->SetTexture(Iterator.first, Iterator.second);
			});
			std::for_each(Uniforms.begin(), Uniforms.end(), [this, PipelineState](pair<string, SharedPointer<Graphics::IUniform>> const & Iterator)
			{
				PipelineState->SetUniform(Iterator.first, Iterator.second);
			});

			Material.LoadTextures();

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
			Loaded[RenderPass] = true;
		}

		void CSimpleSceneObject::Draw(CRenderPass * RenderPass)
		{
			SharedPointer<Graphics::IPipelineState> PipelineState;
			if (TryMapAccess(PipelineStates, RenderPass, PipelineState))
			{
				RenderPass->SubmitPipelineStateForRendering(PipelineState, this);
			}
		}

		void CSimpleSceneObject::SetIndexBuffer(SharedPointer<Graphics::IIndexBuffer> IndexBuffer)
		{
			this->IndexBuffer = IndexBuffer;
		}

		void CSimpleSceneObject::SetVertexBuffer(SharedPointer<Graphics::IVertexBuffer> VertexBuffer)
		{
			this->VertexBuffer = VertexBuffer;
		}

		void CSimpleSceneObject::SetShader(SharedPointer<Graphics::IShaderProgram> Shader)
		{
			this->Shader = Shader;
			TriggerReload();
		}

		void CSimpleSceneObject::SetTexture(string const & Name, SharedPointer<Graphics::ITexture> Texture)
		{
			if (Texture)
			{
				Textures[Name] = Texture;
			}
			else
			{
				Textures.erase(Name);
			}
			TriggerReload();
		}

		void CSimpleSceneObject::SetUniform(string const & Name, SharedPointer<Graphics::IUniform> Uniform)
		{
			if (Uniform)
			{
				Uniforms[Name] = Uniform;
			}
			else
			{
				Uniforms.erase(Name);
			}
			TriggerReload();
		}

		void CSimpleSceneObject::SetFeatureEnabled(Graphics::EDrawFeature const Feature, bool const Enabled)
		{
			for (auto Iterator : PipelineStates)
			{
				Iterator.second->SetFeatureEnabled(Feature, Enabled);
			}

			DrawFeatures[Feature] = Enabled;
		}

		void CSimpleSceneObject::SetBlendMode(Graphics::EBlendMode const BlendMode)
		{
			for (auto Iterator : PipelineStates)
			{
				Iterator.second->SetBlendMode(BlendMode);
			}

			this->BlendMode = BlendMode;
		}

		void CSimpleSceneObject::SetRenderCategory(uint const Category)
		{
			this->RenderCategory = Category;
		}

		SSimpleMaterial & CSimpleSceneObject::GetMaterial()
		{
			return Material;
		}

		SSimpleMaterial const & CSimpleSceneObject::GetMaterial() const
		{
			return Material;
		}

		void CSimpleSceneObject::SetMaterial(SSimpleMaterial const & Material)
		{
			this->Material = Material;
		}

	}
}
