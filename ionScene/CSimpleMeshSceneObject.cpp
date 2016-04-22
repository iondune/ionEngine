
#include "CSimpleMeshSceneObject.h"
#include "CRenderPass.h"


namespace ion
{
	namespace Scene
	{

		void CSimpleMeshSceneObject::Load(CRenderPass * RenderPass)
		{
			if (! Mesh)
			{
				return;
			}

			IndexBuffer = Mesh->CreateIndexBuffer();
			VertexBuffer = Mesh->CreateVertexBuffer();

			CSimpleSceneObject::Load(RenderPass);
		}

		void CSimpleMeshSceneObject::SetMesh(CSimpleMesh * Mesh)
		{
			this->Mesh = Mesh;
			this->Material = Mesh->Material;
			TriggerReload();
		}

	}
}
