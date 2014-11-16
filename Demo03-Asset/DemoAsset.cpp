
#include <ionWindow.h>
#include <ionGL.h>
#include <ionAsset.h>


int main()
{
	SingletonPointer<CWindowManager> WindowManager;

	WindowManager->Init();
	CWindow * Window = WindowManager->CreateWindow(vec2i(800, 600), "TestAsset", EWindowType::Windowed);
		
	string const VertShaderSource = File::ReadAsString("Assets/Shaders/Normals.vert");
	string const FragShaderSource = File::ReadAsString("Assets/Shaders/Normals.frag");

	CMesh * Mesh =
		CGeometryCreator::CreateSphere(vec3f(0.5f), 64, 32);
		//CGeometryCreator::CreateDisc(0.5, 1.5, 0.25, 32, 5);
		//CGeometryCreator::CreateCube();
		//CGeometryCreator::CreateCylinder(2.f, 1.f, 1.f, 32, 16);
	Mesh->LoadDataIntoBuffers();

	CShader * Shader = CompileVertFragShader(VertShaderSource, FragShaderSource);
	Shader->BindAttributeLocation(0, "Position");
	Shader->BindAttributeLocation(1, "Normal");

	CUniformValue<glm::mat4> * Model = new CUniformValue<glm::mat4>;
	CUniformValue<glm::mat4> * View = new CUniformValue<glm::mat4>;
	CUniformValue<glm::mat4> * Projection = new CUniformValue<glm::mat4>;

	View->Value = glm::lookAt(glm::vec3(3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	Projection->Value = glm::perspective(25.0f, 1.333f, 0.1f, 20.f);

	CDrawConfig * Config = new CDrawConfig{Shader};
	Config->AddVertexBuffer("Position", Mesh->Root->Buffers[0]->VertexBuffers.Positions);
	Config->AddVertexBuffer("Normal", Mesh->Root->Buffers[0]->VertexBuffers.Normals);
	Config->AddUniform("Model", Model);
	Config->AddUniform("View", View);
	Config->AddUniform("Projection", Projection);
	Config->SetIndexBuffer(Mesh->Root->Buffers[0]->VertexBuffers.Indices);

	CFrameBuffer * FrameBuffer = new CFrameBuffer;
	FrameBuffer->MakeScreenSizedColorAttachment(0);
	FrameBuffer->MakeScreenSizedDepthTextureAttachment();

	CShader * FXAAShader = CompileVertFragShader(File::ReadAsString("Assets/Shaders/FXAA.vert"), File::ReadAsString("Assets/Shaders/FXAA.frag"));
	CDrawConfig * FXAAConfig = new CDrawConfig(FXAAShader, ion::GL::EPrimitiveType::Quads);
	FXAAConfig->AddVertexBuffer("aPosition", CFrameBuffer::GetQuadVertexBuffer());
	FXAAConfig->SetIndexBuffer(CFrameBuffer::GetQuadIndexBuffer());
	FXAAConfig->AddUniform("uPixelOffset", new CUniformValue<vec2f>(1 / vec2f(ion::GL::Context::GetViewportSize())));
	
	ion::GL::Context::Init();
	while (! WindowManager->ShouldClose())
	{
		WindowManager->PollEvents();

		Model->Value = glm::rotate(Model->Value, 0.0001f, glm::vec3(0, 1, 0.25));
		
		{
			FrameBuffer->Clear();
			CDrawContext DrawContext(FrameBuffer->GetHandle());
			DrawContext.LoadProgram(Shader);
			DrawContext.Draw(Config);
		}
		
		if (Window->IsKeyDown(EKey::F1))
			FrameBuffer->DrawColorAttachmentToScreen(0);
		else if (Window->IsKeyDown(EKey::F2))
			CFrameBuffer::DrawTextureToScreen(FrameBuffer->GetDepthTextureAttachment());
		else
		{
			FXAAConfig->AddTexture("uTexColor", FrameBuffer->GetColorTextureAttachment(0));
			ion::GL::Context::Clear();
			CDrawContext DrawContext;
			DrawContext.LoadProgram(FXAAShader);
			DrawContext.Draw(FXAAConfig);
		}

		Window->SwapBuffers();
	}

	delete Shader;
	delete Mesh;

	return 0;
}
