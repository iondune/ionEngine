
#pragma once

#include "ISceneObject.h"
#include "CSimpleMesh.h"


namespace ion
{
	namespace Scene
	{

		struct SSimpleMaterial
		{

			SSimpleMaterial();
			void LoadDefaults();

			SharedPointer<Graphics::CUniformValue<color3f>> Ambient = std::make_shared<Graphics::CUniformValue<color3f>>();
			SharedPointer<Graphics::CUniformValue<color3f>> Diffuse = std::make_shared<Graphics::CUniformValue<color3f>>();
			SharedPointer<Graphics::CUniformValue<color3f>> Specular = std::make_shared<Graphics::CUniformValue<color3f>>();
			SharedPointer<Graphics::CUniformValue<f32>> Shininess = std::make_shared<Graphics::CUniformValue<f32>>();

		};

		class CSimpleSceneObject : public ISceneObject
		{

		public:

			~CSimpleSceneObject();

			virtual void Load(CRenderPass * RenderPass);
			virtual void Draw(CRenderPass * RenderPass);

			virtual void SetIndexBuffer(SharedPointer<Graphics::IIndexBuffer> IndexBuffer);
			virtual void SetVertexBuffer(SharedPointer<Graphics::IVertexBuffer> VertexBuffer);
			virtual void SetShader(SharedPointer<Graphics::IShaderProgram> Shader);
			virtual void SetTexture(string const & Name, SharedPointer<Graphics::ITexture> Texture);
			virtual void SetUniform(string const & Name, SharedPointer<Graphics::IUniform> Uniform);
			virtual void SetFeatureEnabled(Graphics::EDrawFeature const Feature, bool const Enabled);

			virtual SSimpleMaterial & GetMaterial();
			virtual SSimpleMaterial const & GetMaterial() const;
			virtual void SetMaterial(SSimpleMaterial const & Material);

		protected:

			SharedPointer<Graphics::IPipelineState> PipelineState;
			SharedPointer<Graphics::IShaderProgram> Shader;
			SharedPointer<Graphics::IIndexBuffer> IndexBuffer;
			SharedPointer<Graphics::IVertexBuffer> VertexBuffer;
			SSimpleMaterial Material;

			map<string, SharedPointer<Graphics::ITexture>> Textures;
			map<string, SharedPointer<Graphics::IUniform>> Uniforms;

		};

	}
}
