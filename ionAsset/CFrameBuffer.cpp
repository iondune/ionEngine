
#include "CFrameBuffer.h"


ion::GL::IndexBuffer * CFrameBuffer::QuadIndexBuffer = nullptr;
ion::GL::VertexBuffer * CFrameBuffer::QuadVertexBuffer = nullptr;


void CFrameBuffer::MakeScreenSizedColorAttachment(u32 const Attachment)
{
	CTexture2D * Target = new CTexture2D(ion::GL::Context::GetViewportSize(), false, CTexture2D::EFormatComponents::RGB);
	Target->SetMagFilter(CTexture2D::EFilter::Nearest);
	Target->SetMinFilter(CTexture2D::EFilter::Nearest);
	
	AttachColorTexture(Target, Attachment);
}

void CFrameBuffer::MakeScreenSizedDepthTextureAttachment()
{
	CTexture2D * Target = new CTexture2D(ion::GL::Context::GetViewportSize(), CTexture2D::EDepthComponents::Depth24);
	Target->SetMagFilter(CTexture2D::EFilter::Nearest);
	Target->SetMinFilter(CTexture2D::EFilter::Nearest);
	Target->SetAnisotropy(1);
	
	AttachDepthTexture(Target);
}

void CFrameBuffer::DrawColorAttachmentToScreen(u32 const Attachment)
{
	auto Texture = GetColorTextureAttachment(Attachment);

	if (Texture)
		DrawTextureToScreen(Texture);
}

void CFrameBuffer::DrawTextureToScreen(CTexture2D * Texture)
{
	ion::GL::Context::Clear();
	
	static CShader * Shader = nullptr;
	static CDrawConfig * DrawConfig = nullptr;

	if (! DrawConfig)
	{
		string const VertexShaderSource = R"SHADER(
			#version 150
			in vec2 aPosition;
			out vec2 vTexCoord;

			void main()
			{
				gl_Position = vec4(aPosition, 0, 1);
				vTexCoord = (aPosition + vec2(1.0)) / 2.0;
			}
		)SHADER";

		string const FragmentShaderSource = R"SHADER(
			#version 150
			uniform sampler2D uTexColor;

			in vec2 vTexCoord;
			out vec4 outColor;

			void main()
			{
				outColor = texture2D(uTexColor, vec2(vTexCoord));
			}
		)SHADER";

		Shader = CompileVertFragShader(VertexShaderSource, FragmentShaderSource);

		DrawConfig = new CDrawConfig{Shader, ion::GL::EPrimativeType::Quads};
		DrawConfig->AddVertexBuffer("aPosition", GetQuadVertexBuffer());
		DrawConfig->SetIndexBuffer(GetQuadIndexBuffer());
	}

	DrawConfig->AddTexture("uTexColor", Texture);

	ion::GL::DrawContext DrawContext;
	DrawContext.LoadProgram(Shader);
	DrawContext.Draw(DrawConfig);
}

ion::GL::IndexBuffer * CFrameBuffer::GetQuadIndexBuffer()
{
	if (! QuadIndexBuffer)
	{
		vector<u32> const Indices{
			0, 1, 2, 3
		};

		QuadIndexBuffer = new ion::GL::IndexBuffer;
		QuadIndexBuffer->Data(Indices);
	}

	return QuadIndexBuffer;
}

ion::GL::VertexBuffer * CFrameBuffer::GetQuadVertexBuffer()
{
	if (! QuadVertexBuffer)
	{
		vector<float> QuadVertices
		{
			-1.0, -1.0,
			 1.0, -1.0,
			 1.0,  1.0,
			-1.0,  1.0
		};

		QuadVertexBuffer = new ion::GL::VertexBuffer;
		QuadVertexBuffer->Data(QuadVertices, 2);
	}

	return QuadVertexBuffer;
}
