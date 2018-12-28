
#pragma once

#include "ISceneObject.h"
#include "CSimpleMesh.h"


namespace ion
{
	namespace Scene
	{

		class CSimpleSceneObject : public ISceneObject
		{

		public:

			~CSimpleSceneObject();

			virtual void Load(CRenderPass * RenderPass);
			virtual void Draw(CRenderPass * RenderPass);

			virtual void SetIndexBuffer(SharedPointer<Graphics::IIndexBuffer> IndexBuffer);
			virtual void SetVertexBuffer(uint const Index, SharedPointer<Graphics::IVertexBuffer> VertexBuffer);
			virtual void SetInstanceBuffer(uint const Index, SharedPointer<Graphics::IInstanceBuffer> InstanceBuffer);
			virtual void SetShader(SharedPointer<Graphics::IShader> Shader);
			virtual void SetTexture(string const & Name, SharedPointer<Graphics::ITexture> Texture);
			virtual void SetUniform(string const & Name, SharedPointer<Graphics::IUniform> Uniform);
			virtual void SetFeatureEnabled(Graphics::EDrawFeature const Feature, bool const Enabled);
			virtual void SetPolygonOffsetAmount(float const Amount);
			virtual void SetBlendMode(Graphics::EBlendMode const BlendMode);
			virtual void SetPrimitiveType(Graphics::EPrimitiveType const PrimitiveType);
			virtual void SetRenderCategory(uint const Category);

			template <typename T>
			void SetUniformValue(string const & Name, T const & Value)
			{
				SetUniform(Name, Graphics::CUniform<T>(Value));
			}

			virtual SSimpleMaterial & GetMaterial();
			virtual SSimpleMaterial const & GetMaterial() const;
			virtual void SetMaterial(SSimpleMaterial const & Material);

		protected:

			map<CRenderPass *, SharedPointer<Graphics::IPipelineState>> PipelineStates;
			SharedPointer<Graphics::IShader> Shader;

			SharedPointer<Graphics::IIndexBuffer> IndexBuffer;
			vector<SharedPointer<Graphics::IVertexBuffer>> VertexBuffers;
			vector<SharedPointer<Graphics::IInstanceBuffer>> InstanceBuffers;
			SSimpleMaterial Material;

			map<string, SharedPointer<Graphics::ITexture>> Textures;
			map<string, SharedPointer<Graphics::IUniform>> Uniforms;
			map<Graphics::EDrawFeature, bool> DrawFeatures;
			float PolygonOffsetAmount = 1.f;
			Graphics::EBlendMode BlendMode = Graphics::EBlendMode::None;
			Graphics::EPrimitiveType PrimitiveType = Graphics::EPrimitiveType::Triangle;
			uint RenderCategory = 0;

		};

	}
}
