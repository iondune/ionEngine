
#include <ionWindow.h>
#include <ionFramework.h>
#include <ionGraphics.h>
#include <ionGraphicsGL.h>


using namespace ion;
using namespace ion::Graphics;


int main()
{
	////////////////////
	// ionEngine Init //
	////////////////////

	Log::AddDefaultOutputs();

	SingletonPointer<CWindowManager> WindowManager;
	SingletonPointer<CTimeManager> TimeManager;
	WindowManager->Init();
	TimeManager->Init();

	CWindow * Window = WindowManager->CreateWindow(vec2i(640, 480), "TestGL", EWindowType::Windowed);

	IGraphicsAPI * GraphicsAPI = new COpenGLAPI();
	SharedPtr<IGraphicsContext> Context = GraphicsAPI->GetWindowContext(Window);
	SharedPtr<IRenderTarget> RenderTarget = Context->GetBackBuffer();

	//////////////////
	// Buffer Setup //
	//////////////////

	vector<f32> const Vertices
	{
		// Position    // Tex  // Color
		 0.5f,  0.5f,   1, 1,   1, 0, 0,
		 0.5f, -0.5f,   1, 0,   0, 1, 0,
		-0.5f, -0.5f,   0, 0,   0, 0, 1,
		-0.5f,  0.5f,   0, 1,   0, 1, 1,
	};

	vector<u32> const Indices
	{
		0, 1, 2,
		0, 2, 3,
	};


	SharedPtr<IIndexBuffer> IndexBuffer = GraphicsAPI->CreateIndexBuffer();
	IndexBuffer->UploadData(Indices);
	SharedPtr<IVertexBuffer> VertexBuffer = GraphicsAPI->CreateVertexBuffer();
	VertexBuffer->UploadData(Vertices);
	SInputLayoutElement InputLayout[] =
	{
		{ "vPosition", 2, EAttributeType::Float },
		{ "vTexCoords", 2, EAttributeType::Float },
		{ "vColor", 3, EAttributeType::Float },
	};
	VertexBuffer->SetInputLayout(InputLayout, ION_ARRAYSIZE(InputLayout));
	

	//////////////////
	// Shader Setup //
	//////////////////

	string const VertexShaderSource = R"SHADER(
		#version 330

		in vec2 vPosition;
		in vec2 vTexCoords;
		in vec3 vColor;

		out vec2 fTexCoords;
		out vec3 fColor;

		void main()
		{
			gl_Position = vec4(vPosition, 0.0, 1.0);
			fTexCoords = vTexCoords;
			fColor = vColor;
		}
	)SHADER";

	string const FragmentShaderSource = R"SHADER(
		#version 330

		in vec2 fTexCoords;
		in vec3 fColor;
		uniform float uCurrentTime; 
		uniform sampler2D uTexture;
		out vec4 outColor;

		void main()
		{
			const float Pi = 3.1415926535897932384626433832795;

			float Alpha = (cos(uCurrentTime * 3.0) + 1.0) / 2.0;
			float Visibility = sin(uCurrentTime * 1.5 + Pi / 2.0);
			outColor = vec4(fColor * Alpha, 1.0);
			if (Visibility < 0.0)
				outColor.rgb *= texture(uTexture, fTexCoords).rgb;
		}
	)SHADER";

	SharedPtr<IVertexShader> VertexShader = GraphicsAPI->CreateVertexShaderFromSource(VertexShaderSource);
	SharedPtr<IPixelShader> PixelShader = GraphicsAPI->CreatePixelShaderFromSource(FragmentShaderSource);

	if (! VertexShader)
		std::cerr << "Failed to compile vertex shader!" << std::endl;

	if (! PixelShader)
		std::cerr << "Failed to compile pixel shader!" << std::endl;

	SharedPtr<IShaderProgram> ShaderProgram = GraphicsAPI->CreateShaderProgram();
	ShaderProgram->SetVertexStage(VertexShader);
	ShaderProgram->SetPixelStage(PixelShader);
	

	///////////////
	// Draw Loop //
	///////////////

	SharedPtr<IPipelineState> PipelineState = Context->CreatePipelineState();
	PipelineState->SetIndexBuffer(IndexBuffer);
	PipelineState->SetVertexBuffer(0, VertexBuffer);
	PipelineState->SetProgram(ShaderProgram);

	SharedPtr<CUniformValue<float>> uCurrentTime = std::make_shared<CUniformValue<float>>();
	PipelineState->SetUniform("uCurrentTime", uCurrentTime);

	CImage * Image = CImage::Load("Image.jpg");
	SharedPtr<ITexture2D> Texture = GraphicsAPI->CreateTexture2D(Image->GetSize(), ITexture::EMipMaps::True, ITexture::EFormatComponents::RGB, ITexture::EInternalFormatType::Fix8);
	Texture->Upload(Image->GetData(), Image->GetSize(), ITexture::EFormatComponents::RGB, EScalarType::UnsignedInt8);
	PipelineState->SetTexture("uTexture", Texture);

	PipelineState->Load();

	while (WindowManager->Run())
	{
		TimeManager->Update();
		*uCurrentTime = (float) TimeManager->GetRunTime();

		RenderTarget->ClearColorAndDepth();
		Context->Draw(PipelineState);
		Window->SwapBuffers();
	}


	/////////////
	// Cleanup //
	/////////////

	return 0;
}
