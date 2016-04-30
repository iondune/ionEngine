
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
			virtual void SetShader(SharedPointer<Graphics::IShaderProgram> Shader);
			virtual void SetTexture(string const & Name, SharedPointer<Graphics::ITexture> Texture);
			virtual void SetUniform(string const & Name, SharedPointer<Graphics::IUniform> Uniform);
			virtual void SetFeatureEnabled(Graphics::EDrawFeature const Feature, bool const Enabled);
			virtual void SetBlendMode(Graphics::EBlendMode const BlendMode);
			virtual void SetRenderCategory(uint const Category);
			virtual void SetInstanceCount(uint const InstanceCount);

			virtual SSimpleMaterial & GetMaterial();
			virtual SSimpleMaterial const & GetMaterial() const;
			virtual void SetMaterial(SSimpleMaterial const & Material);

		protected:

			map<CRenderPass *, SharedPointer<Graphics::IPipelineState>> PipelineStates;
			SharedPointer<Graphics::IShaderProgram> Shader;

			SharedPointer<Graphics::IIndexBuffer> IndexBuffer;
			vector<SharedPointer<Graphics::IVertexBuffer>> VertexBuffers;
			SSimpleMaterial Material;

			map<string, SharedPointer<Graphics::ITexture>> Textures;
			map<string, SharedPointer<Graphics::IUniform>> Uniforms;
			map<Graphics::EDrawFeature, bool> DrawFeatures;
			Graphics::EBlendMode BlendMode = Graphics::EBlendMode::None;
			uint RenderCategory = 0;
			uint InstanceCount = 1;

		};

	}
}
