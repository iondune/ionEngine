
#include "CCoordinateFrameSceneObject.h"
#include "CRenderPass.h"


using namespace ion::Graphics;

namespace ion
{
	namespace Scene
	{
		
		CCoordinateFrameSceneObject::CCoordinateFrameSceneObject()
		{}

		CCoordinateFrameSceneObject::~CCoordinateFrameSceneObject()
		{}

		void CCoordinateFrameSceneObject::Load(CRenderPass * RenderPass)
		{
			SingletonPointer<CGraphicsAPI> GraphicsAPI;

			vector<float> const Vertices
			{
				0, 0, 0,  1, 0, 0,
				1, 0, 0,  1, 0, 0,
				0, 0, 0,  0, 1, 0,
				0, 1, 0,  0, 1, 0,
				0, 0, 0,  0, 0, 1,
				0, 0, 1,  0, 0, 1,
			};

			vector<uint> const Indices
			{
				0, 1,
				2, 3,
				4, 5,
			};

			SharedPointer<IIndexBuffer> IndexBuffer = GraphicsAPI->CreateIndexBuffer();
			IndexBuffer->UploadData(Indices);
			SharedPointer<IVertexBuffer> VertexBuffer = GraphicsAPI->CreateVertexBuffer();
			VertexBuffer->UploadData(Vertices);
			SInputLayoutElement InputLayout[] =
			{
				{ "vPosition", 3, EAttributeType::Float },
				{ "vColor", 3, EAttributeType::Float },
			};
			VertexBuffer->SetInputLayout(InputLayout, ION_ARRAYSIZE(InputLayout));

			PipelineState = RenderPass->GetGraphicsContext()->CreatePipelineState();
			PipelineState->SetProgram(Shader);
			PipelineState->SetIndexBuffer(IndexBuffer);
			PipelineState->SetVertexBuffer(0, VertexBuffer);
			PipelineState->SetPrimitiveType(EPrimitiveType::Line);

			RenderPass->PreparePipelineStateForRendering(PipelineState, this);
			Loaded[RenderPass] = true;
		}

		void CCoordinateFrameSceneObject::Draw(CRenderPass * RenderPass)
		{
			RenderPass->SubmitPipelineStateForRendering(PipelineState, this);
		}

		void CCoordinateFrameSceneObject::SetShader(SharedPointer<Graphics::IShaderProgram> Shader)
		{
			this->Shader = Shader;
			TriggerReload();
		}

	}
}
