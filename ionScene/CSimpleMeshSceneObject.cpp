
#include "CSimpleMeshSceneObject.h"
#include "CRenderPass.h"


namespace ion
{
	namespace Scene
	{

		void CSimpleMeshSceneObject::Load(CRenderPass * RenderPass)
		{
			if (! PipelineState)
			{
				PipelineState = RenderPass->GetGraphicsAPI()->CreatePipelineState();
			}

			if (! Mesh)
			{
				
			}
		}

		void CSimpleMeshSceneObject::Draw(CRenderPass * RenderPass)
		{
		}

		void CSimpleMeshSceneObject::SetMesh(CSimpleMesh * Mesh)
		{
			this->Mesh = Mesh;
		}

		void CSimpleMeshSceneObject::SetShader(Graphics::IShaderProgram * Shader)
		{
			this->Shader = Shader;
		}

	}
}
