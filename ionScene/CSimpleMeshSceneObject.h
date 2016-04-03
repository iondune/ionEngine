
#pragma once

#include "ISceneObject.h"
#include "CSimpleMesh.h"
#include "CSimpleSceneObject.h"


namespace ion
{
	namespace Scene
	{

		class CSimpleMeshSceneObject : public ISceneObject
		{

		public:

			~CSimpleMeshSceneObject();

			virtual void Load(CRenderPass * RenderPass);
			virtual void Draw(CRenderPass * RenderPass);

			virtual void SetMesh(CSimpleMesh * Mesh);
			virtual void SetShader(SharedPointer<Graphics::IShaderProgram> Shader);
			virtual void SetTexture(string const & Name, SharedPointer<Graphics::ITexture> Texture);
			virtual void SetUniform(string const & Name, SharedPointer<Graphics::IUniform> Uniform);
			virtual void SetFeatureEnabled(Graphics::EDrawFeature const Feature, bool const Enabled);
			virtual void SetBlendMode(Graphics::EBlendMode const BlendMode);
			virtual void SetRenderCategory(uint const Category);

			virtual SSimpleMaterial & GetMaterial();
			virtual SSimpleMaterial const & GetMaterial() const;
			virtual void SetMaterial(SSimpleMaterial const & Material);

		protected:

			CSimpleMesh * Mesh = nullptr;

			SharedPointer<Graphics::IPipelineState> PipelineState;
			SharedPointer<Graphics::IShaderProgram> Shader;
			SharedPointer<Graphics::IIndexBuffer> IndexBuffer;
			SharedPointer<Graphics::IVertexBuffer> VertexBuffer;
			SSimpleMaterial Material;

			map<string, SharedPointer<Graphics::ITexture>> Textures;
			map<string, SharedPointer<Graphics::IUniform>> Uniforms;
			map<Graphics::EDrawFeature, bool> DrawFeatures;
			Graphics::EBlendMode BlendMode = Graphics::EBlendMode::None;
			uint RenderCategory = 0;

		};

	}
}
