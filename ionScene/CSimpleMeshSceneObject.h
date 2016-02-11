
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

			virtual void Load(CRenderPass * RenderPass);
			virtual void Draw(CRenderPass * RenderPass);

			virtual void SetMesh(CSimpleMesh * Mesh);
			virtual void SetShader(Graphics::IShaderProgram * Shader);
			virtual void SetTexture(string const & Name, Graphics::ITexture * Texture);

			virtual SSimpleMaterial & GetMaterial();
			virtual SSimpleMaterial const & GetMaterial() const;
			virtual void SetMaterial(SSimpleMaterial const & Material);

		protected:

			Graphics::IPipelineState * PipelineState = nullptr;
			CSimpleMesh * Mesh = nullptr;
			Graphics::IShaderProgram * Shader = nullptr;
			SSimpleMaterial Material;

			map<string, Graphics::ITexture *> Textures;

		};

	}
}
