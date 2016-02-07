
#pragma once

#include "ISceneObject.h"
#include "CSimpleMesh.h"


namespace ion
{
	namespace Scene
	{

		class CSimpleMeshSceneObject : public ISceneObject
		{

		public:

			virtual void Load(CRenderPass * RenderPass);
			virtual void Draw(CRenderPass * RenderPass);

			virtual void SetMesh(CSimpleMesh * Mesh);
			virtual void SetShader(Graphics::IShaderProgram * Shader);

		protected:

			Graphics::IPipelineState * PipelineState = nullptr;
			CSimpleMesh * Mesh = nullptr;
			Graphics::IShaderProgram * Shader = nullptr;

		};

	}
}
