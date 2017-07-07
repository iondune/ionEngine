
#pragma once

#include "ISceneObject.h"
#include "CSimpleMesh.h"


namespace ion
{
	namespace Scene
	{

		class CCoordinateFrameSceneObject : public ISceneObject
		{

		public:

			CCoordinateFrameSceneObject();
			~CCoordinateFrameSceneObject();

			virtual void Load(CRenderPass * RenderPass);
			virtual void Draw(CRenderPass * RenderPass);

			virtual void SetShader(SharedPointer<Graphics::IShader> Shader);

		protected:

			SharedPointer<Graphics::IPipelineState> PipelineState;
			SharedPointer<Graphics::IShader> Shader;

			SharedPointer<Graphics::IIndexBuffer> IndexBuffer;
			SharedPointer<Graphics::IVertexBuffer> VertexBuffers;

		};

	}
}
