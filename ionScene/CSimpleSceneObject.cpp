
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
			if (! IndexBuffer || ! VertexBuffers.size() || ! Shader)
			{
				return;
			}

			SharedPointer<Graphics::IPipelineState> PipelineState;
			if (! TryMapAccess(PipelineStates, RenderPass, PipelineState))
			{
				PipelineStates[RenderPass] = PipelineState = RenderPass->GetGraphicsContext()->CreatePipelineState();
			}

			PipelineState->SetIndexBuffer(IndexBuffer);
			for (uint i = 0; i < VertexBuffers.size(); ++ i)
			{
				PipelineState->SetVertexBuffer(i, VertexBuffers[i]);
			}

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
			PipelineState->SetPolygonOffsetAmount(PolygonOffsetAmount);
			PipelineState->SetBlendMode(BlendMode);

			RenderPass->PreparePipelineStateForRendering(PipelineState, this);
			Loaded[RenderPass] = true;
		}

		void CSimpleSceneObject::Draw(CRenderPass * RenderPass)
		{
			SharedPointer<Graphics::IPipelineState> PipelineState;
			if (TryMapAccess(PipelineStates, RenderPass, PipelineState))
			{
				RenderPass->SubmitPipelineStateForRendering(PipelineState, this, InstanceCount, RenderCategory);
			}
		}

		void CSimpleSceneObject::SetIndexBuffer(SharedPointer<Graphics::IIndexBuffer> IndexBuffer)
		{
			this->IndexBuffer = IndexBuffer;
			TriggerReload();
		}

		void CSimpleSceneObject::SetVertexBuffer(uint const Index, SharedPointer<Graphics::IVertexBuffer> VertexBuffer)
		{
			if (VertexBuffers.size() <= Index)
			{
				VertexBuffers.resize(Index + 1);
			}
			VertexBuffers[Index] = VertexBuffer;
			TriggerReload();
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

		void CSimpleSceneObject::SetPolygonOffsetAmount(float const Amount)
		{
			for (auto Iterator : PipelineStates)
			{
				Iterator.second->SetPolygonOffsetAmount(Amount);
			}

			PolygonOffsetAmount = Amount;
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

		void CSimpleSceneObject::SetInstanceCount(uint const InstanceCount)
		{
			this->InstanceCount = InstanceCount;
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
