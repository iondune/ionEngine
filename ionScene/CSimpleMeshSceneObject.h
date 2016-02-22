
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

			Graphics::CUniformValue<color3f> Ambient, Diffuse, Specular;
			Graphics::CUniformValue<f32> Shininess;

		};

		class CSimpleMeshSceneObject : public ISceneObject
		{

		public:

			~CSimpleMeshSceneObject();

			virtual void Load(CRenderPass * RenderPass);
			virtual void Draw(CRenderPass * RenderPass);

			virtual void SetMesh(CSimpleMesh * Mesh);
			virtual void SetShader(Graphics::IShaderProgram * Shader);
			virtual void SetTexture(string const & Name, Graphics::ITexture * Texture);

			virtual SSimpleMaterial & GetMaterial();
			virtual SSimpleMaterial const & GetMaterial() const;
			virtual void SetMaterial(SSimpleMaterial const & Material);

		protected:

			CSimpleMesh * Mesh = nullptr;

			Graphics::IPipelineState * PipelineState = nullptr;
			Graphics::IShaderProgram * Shader = nullptr;
			Graphics::IIndexBuffer * IndexBuffer = nullptr;
			Graphics::IVertexBuffer * VertexBuffer = nullptr;
			SSimpleMaterial Material;

			map<string, Graphics::ITexture *> Textures;

		};

	}
}
