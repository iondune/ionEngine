
#include "CLineSceneObject.h"
#include "CRenderPass.h"


namespace ion
{

	namespace Scene
	{

		CLineSceneObject::CLineSceneObject()
		{

		}

		CLineSceneObject::~CLineSceneObject()
		{

		}

		void CLineSceneObject::Load(CRenderPass * RenderPass)
		{
			SingletonPointer<CGraphicsAPI> GraphicsAPI;

			IndexBuffer = GraphicsAPI->CreateIndexBuffer();
			VertexBuffer = GraphicsAPI->CreateVertexBuffer();
			Graphics::SInputLayoutElement InputLayout[] =
			{
				{ "vPosition", 3, Graphics::EAttributeType::Float },
				{ "vColor",    3, Graphics::EAttributeType::Float },
			};
			VertexBuffer->SetInputLayout(InputLayout, ION_ARRAYSIZE(InputLayout));

			PipelineState = RenderPass->GetGraphicsContext()->CreatePipelineState();
			PipelineState->SetShader(Shader);
			PipelineState->SetIndexBuffer(IndexBuffer);
			PipelineState->SetVertexBuffer(0, VertexBuffer);
			PipelineState->SetPrimitiveType(Graphics::EPrimitiveType::Line);

			RenderPass->PreparePipelineStateForRendering(PipelineState, this);
			Loaded[RenderPass] = true;

		}

		void CLineSceneObject::Draw(CRenderPass * RenderPass)
		{
			if (DataNeedsUpload)
			{
				IndexBuffer->UploadData(Indices);
				VertexBuffer->UploadData(Vertices);

				DataNeedsUpload = false;
			}

			RenderPass->SubmitPipelineStateForRendering(PipelineState, this, 1, RenderCategory);
		}

		void CLineSceneObject::SetShader(SharedPointer<Graphics::IShader> Shader)
		{
			this->Shader = Shader;
			TriggerReload();
		}

		void CLineSceneObject::SetFeatureEnabled(Graphics::EDrawFeature const Feature, bool const Enabled)
		{
			PipelineState->SetFeatureEnabled(Feature, Enabled);
		}

		void CLineSceneObject::SetRenderCategory(int const Category)
		{
			this->RenderCategory = Category;
		}

		void CLineSceneObject::ResetLines()
		{
			DataNeedsUpload = true;
			Vertices.clear();
			Indices.clear();
			IndexCounter = 0;
		}

		void CLineSceneObject::AddLine(vec3f const & A, vec3f const & B, color3f const & Color)
		{
			DataNeedsUpload = true;

			Vertices.push_back(A.X);
			Vertices.push_back(A.Y);
			Vertices.push_back(A.Z);

			Vertices.push_back(Color.Red);
			Vertices.push_back(Color.Green);
			Vertices.push_back(Color.Blue);

			Vertices.push_back(B.X);
			Vertices.push_back(B.Y);
			Vertices.push_back(B.Z);

			Vertices.push_back(Color.Red);
			Vertices.push_back(Color.Green);
			Vertices.push_back(Color.Blue);

			Indices.push_back((uint) IndexCounter++);
			Indices.push_back((uint) IndexCounter++);
		}

		void CLineSceneObject::AddStar(vec3f const & P, float const R, color3f const & Color)
		{
			AddLine(P - vec3f(R, 0, 0), P + vec3f(R, 0, 0), Color);
			AddLine(P - vec3f(0, R, 0), P + vec3f(0, R, 0), Color);
			AddLine(P - vec3f(0, 0, R), P + vec3f(0, 0, R), Color);
		
			AddLine(P + vec3f(-R, -R, R), P + vec3f(R, R, -R), Color);
			AddLine(P + vec3f(R, -R, -R), P + vec3f(-R, R, R), Color);
			AddLine(P + vec3f(-R, -R, -R), P + vec3f(R, R, R), Color);
			AddLine(P + vec3f(R, -R, R), P + vec3f(-R, R, -R), Color);
		}

	}

}
