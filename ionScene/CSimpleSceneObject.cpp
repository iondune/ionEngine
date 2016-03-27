
#include "CSimpleSceneObject.h"
#include "CRenderPass.h"


namespace ion
{
	namespace Scene
	{

		SSimpleMaterial::SSimpleMaterial()
		{
			Shininess = 1000.0f;
			Ambient = SColorf(0.05f);
			Diffuse = SColorf(0.9f);
			Specular = SColorf(1.f);
		}

		void SSimpleMaterial::LoadTextures(Graphics::IGraphicsAPI * GraphicsAPI)
		{
			static auto LoadTexture = [](Graphics::IGraphicsAPI * GraphicsAPI, CImage * Image) -> SharedPointer<Graphics::ITexture2D>
			{
				SharedPointer<Graphics::ITexture2D> Texture;
				if (Image)
				{
					Graphics::ITexture::EFormatComponents Format = Graphics::ITexture::EFormatComponents::R;
					switch (Image->GetChannels())
					{
					case 2:
						Format = Graphics::ITexture::EFormatComponents::RG;
						break;
					case 3:
						Format = Graphics::ITexture::EFormatComponents::RGB;
						break;
					case 4:
						Format = Graphics::ITexture::EFormatComponents::RGBA;
						break;
					}
					Texture = GraphicsAPI->CreateTexture2D(
						Image->GetSize(),
						Graphics::ITexture::EMipMaps::True,
						Format,
						Graphics::ITexture::EInternalFormatType::Fix8);
					Texture->Upload(
						Image->GetData(),
						Image->GetSize(),
						Format,
						Graphics::EScalarType::UnsignedInt8);
				}
				return Texture;
			};

			if (! DiffuseTexture)
			{
				DiffuseTexture = LoadTexture(GraphicsAPI, DiffuseImage);
			}

			if (! AmbientTexture)
			{
				AmbientTexture = LoadTexture(GraphicsAPI, AmbientImage);
			}
		}

		CSimpleSceneObject::~CSimpleSceneObject()
		{}

		void CSimpleSceneObject::Load(CRenderPass * RenderPass)
		{
			if (! IndexBuffer || ! VertexBuffer || ! Shader)
			{
				return;
			}

			if (! PipelineState)
			{
				PipelineState = RenderPass->GetGraphicsContext()->CreatePipelineState();
			}

			PipelineState->SetIndexBuffer(IndexBuffer);
			PipelineState->SetVertexBuffer(0, VertexBuffer);

			PipelineState->SetProgram(Shader);

			std::for_each(Textures.begin(), Textures.end(), [this](pair<string, SharedPointer<Graphics::ITexture>> const & Iterator)
			{
				PipelineState->SetTexture(Iterator.first, Iterator.second);
			});
			std::for_each(Uniforms.begin(), Uniforms.end(), [this](pair<string, SharedPointer<Graphics::IUniform>> const & Iterator)
			{
				PipelineState->SetUniform(Iterator.first, Iterator.second);
			});

			Material.LoadTextures(RenderPass->GetGraphicsAPI());

			PipelineState->OfferUniform("uMaterial.AmbientColor", Material.Ambient);
			PipelineState->OfferUniform("uMaterial.DiffuseColor", Material.Diffuse);
			PipelineState->OfferUniform("uMaterial.SpecularColor", Material.Specular);
			PipelineState->OfferUniform("uMaterial.Shininess", Material.Shininess);
			PipelineState->OfferTexture("uMaterial.DiffuseTexture", Material.DiffuseTexture);

			RenderPass->PreparePipelineStateForRendering(PipelineState, this);
			Loaded = true;
		}

		void CSimpleSceneObject::Draw(CRenderPass * RenderPass)
		{
			if (PipelineState)
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
			Loaded = false;
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
			Loaded = false;
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
			Loaded = false;
		}

		void CSimpleSceneObject::SetFeatureEnabled(Graphics::EDrawFeature const Feature, bool const Enabled)
		{
			if (PipelineState)
			{
				PipelineState->SetFeatureEnabled(Feature, Enabled);
			}
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
