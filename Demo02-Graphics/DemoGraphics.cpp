
#include <ionWindow.h>
#include <ionGraphics.h>
#include <ionGraphicsD3D11.h>


using namespace ion;
using namespace ion::Graphics;


int main()
{
	////////////////////
	// ionEngine Init //
	////////////////////

	Log::AddDefaultOutputs();

	SingletonPointer<CGraphicsAPI> GraphicsAPI;
	SingletonPointer<CWindowManager> WindowManager;
	SingletonPointer<CTimeManager> TimeManager;

	GraphicsAPI->Init(new Graphics::CD3D11Implementation());
	WindowManager->Init(GraphicsAPI);
	TimeManager->Init(WindowManager);

	CWindow * Window = WindowManager->CreateWindow(vec2i(640, 480), "DemoGraphics", EWindowType::Windowed);

	SharedPointer<IGraphicsContext> Context = GraphicsAPI->GetWindowContext(Window);
	SharedPointer<IRenderTarget> RenderTarget = Context->GetBackBuffer();
	RenderTarget->SetClearColor(color3f(0.3f));

	//////////////////
	// Buffer Setup //
	//////////////////

	vector<float> const Vertices
	{
		// Position     // Tex  // Color
		 0.5f,  0.5f,   1, 1,   1, 0, 0,
		 0.5f, -0.5f,   1, 0,   0, 1, 0,
		-0.5f, -0.5f,   0, 0,   0, 0, 1,
		-0.5f,  0.5f,   0, 1,   0, 1, 1,
	};

	vector<uint> const Indices
	{
		0, 1, 2,
		0, 2, 3,
	};


	SharedPointer<IIndexBuffer> IndexBuffer = GraphicsAPI->CreateIndexBuffer();
	IndexBuffer->UploadData(Indices);
	SharedPointer<IVertexBuffer> VertexBuffer = GraphicsAPI->CreateVertexBuffer();
	VertexBuffer->UploadData(Vertices);
	SInputLayoutElement InputLayout[] =
	{
		{ "vPosition", 2, EAttributeType::Float },
		{ "vTexCoord", 2, EAttributeType::Float },
		{ "vColor",    3, EAttributeType::Float },
	};
	VertexBuffer->SetInputLayout(InputLayout, ION_ARRAYSIZE(InputLayout));
	

	//////////////////
	// Shader Setup //
	//////////////////

	SharedPointer<IVertexStage> VertexStage = GraphicsAPI->CreateVertexStageFromFile("Shader.hlsl");
	SharedPointer<IPixelStage> PixelStage = GraphicsAPI->CreatePixelStageFromFile("Shader.hlsl");

	if (! VertexStage)
		std::cerr << "Failed to compile vertex shader!" << std::endl;

	if (! PixelStage)
		std::cerr << "Failed to compile pixel shader!" << std::endl;

	SharedPointer<IShader> Shader = GraphicsAPI->CreateShaderProgram();
	Shader->SetVertexStage(VertexStage);
	Shader->SetPixelStage(PixelStage);
	

	///////////////
	// Draw Loop //
	///////////////

	SharedPointer<IPipelineState> PipelineState = Context->CreatePipelineState();
	PipelineState->SetIndexBuffer(IndexBuffer);
	PipelineState->SetVertexBuffer(0, VertexBuffer);
	PipelineState->SetShader(Shader);

	CUniform<float> uCurrentTime;
	PipelineState->SetUniform("uCurrentTime", uCurrentTime);

	CImage * Image = CImage::Load("Image.jpg");
	SharedPointer<ITexture2D> Texture = GraphicsAPI->CreateTexture2D(Image->GetSize(), ITexture::EMipMaps::True, ITexture::EFormatComponents::RGBA, ITexture::EInternalFormatType::Fix8);
	Texture->Upload(Image->GetData(), Image->GetSize(), ITexture::EFormatComponents::RGBA, EScalarType::UnsignedInt8);
	PipelineState->SetTexture("uTexture", Texture);

	PipelineState->Load();

	while (WindowManager->Run())
	{
		TimeManager->Update();
		uCurrentTime = (float) TimeManager->GetRunTime();

		RenderTarget->Bind();
		RenderTarget->ClearColorAndDepth();
		Context->Draw(PipelineState);
		Window->SwapBuffers();
	}


	/////////////
	// Cleanup //
	/////////////

	return 0;
}
