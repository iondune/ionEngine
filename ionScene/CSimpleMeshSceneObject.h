
#pragma once

#include "ISceneObject.h"
#include "CSimpleMesh.h"
#include "CSimpleSceneObject.h"


namespace ion
{
	namespace Scene
	{

		class CSimpleMeshSceneObject : public CSimpleSceneObject
		{

		public:

			virtual void Load(CRenderPass * RenderPass);

			virtual void SetMesh(CSimpleMesh * Mesh);

		protected:

			CSimpleMesh * Mesh = nullptr;

		};

	}
}
