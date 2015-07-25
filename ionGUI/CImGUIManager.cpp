
#include "CImGUIManager.h"
#include <GL/glew.h>


// This is the main rendering function that you have to implement and provide to ImGui (via setting up 'RenderDrawListsFn' in the ImGuiIO structure)
// If text or lines are blurry when integrating ImGui in your engine:
// - in your Render function, try translating your projection matrix by (0.5f,0.5f) or (0.375f,0.375f)
void CImGUIManager::DrawCallback(ImDrawData* draw_data)
{
	// Setup render state: alpha-blending enabled, no face culling, no depth testing, scissor enabled
	GLint last_program, last_texture;
	glGetIntegerv(GL_CURRENT_PROGRAM, &last_program);
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_SCISSOR_TEST);
	glActiveTexture(GL_TEXTURE0);

	// Setup orthographic projection matrix
	const float width = ImGui::GetIO().DisplaySize.x;
	const float height = ImGui::GetIO().DisplaySize.y;
	const float ortho_projection[4][4] =
	{
		{ 2.0f / width, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 2.0f / -height, 0.0f, 0.0f },
		{ 0.0f, 0.0f, -1.0f, 0.0f },
		{ -1.0f, 1.0f, 0.0f, 1.0f },
	};
	glUseProgram(ShaderHandle);
	glUniform1i(AttribLocationTex, 0);
	glUniformMatrix4fv(AttribLocationProjMtx, 1, GL_FALSE, &ortho_projection[0][0]);
	glBindVertexArray(VaoHandle);

	for (int n = 0; n < draw_data->CmdListsCount; n++)
	{
		const ImDrawList* cmd_list = draw_data->CmdLists[n];
		const ImDrawIdx* idx_buffer = &cmd_list->IdxBuffer.front();

		glBindBuffer(GL_ARRAY_BUFFER, VboHandle);
		int needed_vtx_size = cmd_list->VtxBuffer.size() * sizeof(ImDrawVert);
		if (VboSize < needed_vtx_size)
		{
			// Grow our buffer if needed
			VboSize = needed_vtx_size + 2000 * sizeof(ImDrawVert);
			glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr) VboSize, NULL, GL_STREAM_DRAW);
		}

		unsigned char* vtx_data = (unsigned char*) glMapBufferRange(GL_ARRAY_BUFFER, 0, needed_vtx_size, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
		if (!vtx_data)
			continue;
		memcpy(vtx_data, &cmd_list->VtxBuffer[0], cmd_list->VtxBuffer.size() * sizeof(ImDrawVert));
		glUnmapBuffer(GL_ARRAY_BUFFER);

		for (const ImDrawCmd* pcmd = cmd_list->CmdBuffer.begin(); pcmd != cmd_list->CmdBuffer.end(); pcmd++)
		{
			if (pcmd->UserCallback)
			{
				pcmd->UserCallback(cmd_list, pcmd);
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D, (GLuint) (intptr_t) pcmd->TextureId);
				glScissor((int) pcmd->ClipRect.x, (int) (height - pcmd->ClipRect.w), (int) (pcmd->ClipRect.z - pcmd->ClipRect.x), (int) (pcmd->ClipRect.w - pcmd->ClipRect.y));
				glDrawElements(GL_TRIANGLES, (GLsizei) pcmd->ElemCount, GL_UNSIGNED_SHORT, idx_buffer);
			}
			idx_buffer += pcmd->ElemCount;
		}
	}

	// Restore modified state
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(last_program);
	glDisable(GL_SCISSOR_TEST);
	glEnable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, last_texture);
}

void CImGUIManager::OnEvent(IEvent & Event)
{
	ImGuiIO& io = ImGui::GetIO();

	if (InstanceOf<SKeyboardEvent>(Event))
	{
		SKeyboardEvent KeyboardEvent = As<SKeyboardEvent>(Event);
		io.KeysDown[(int) KeyboardEvent.Key] = KeyboardEvent.Pressed;
		io.KeyCtrl = Window->IsKeyDown(EKey::LeftControl) || Window->IsKeyDown(EKey::RightControl);
		io.KeyShift = Window->IsKeyDown(EKey::LeftShift) || Window->IsKeyDown(EKey::RightShift);
		io.KeyAlt = Window->IsKeyDown(EKey::LeftAlt) || Window->IsKeyDown(EKey::RightAlt);
	}
	else if (InstanceOf<SMouseEvent>(Event))
	{
		SMouseEvent MouseEvent = As<SMouseEvent>(Event);
		switch (MouseEvent.Type)
		{
		case SMouseEvent::EType::Click:
			MousePressed[(int) MouseEvent.Button] = MouseEvent.Pressed;
			break;
		case SMouseEvent::EType::Move:
			break;
		case SMouseEvent::EType::Scroll:
			MouseWheel += MouseEvent.Movement.Y;
			break;
		}
	}
	else if (InstanceOf<SCharacterEvent>(Event))
	{
		SCharacterEvent CharacterEvent = As<SCharacterEvent>(Event);
		if (CharacterEvent.C > 0 && CharacterEvent.C < 0x10000)
			io.AddInputCharacter(CharacterEvent.C);
	}
}

void CImGUIManager::CreateFontsTexture()
{
	ImGuiIO& io = ImGui::GetIO();

	unsigned char* pixels;
	int width, height;
	io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);   // Load as RGBA 32-bits for OpenGL3 demo because it is more likely to be compatible with user's existing shader.

	glGenTextures(1, &FontTexture);
	glBindTexture(GL_TEXTURE_2D, FontTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	// Store our identifier
	io.Fonts->TexID = (void *) (intptr_t) FontTexture;
}

void CImGUIManager::AddFontFromFile(string const & FileName, float const Size)
{
	ImGuiIO& io = ImGui::GetIO();
	ImFont* my_font = io.Fonts->AddFontFromFileTTF(FileName.c_str(), Size);
}

bool CImGUIManager::CreateDeviceObjects()
{
	const GLchar *vertex_shader =
		"#version 330\n"
		"uniform mat4 ProjMtx;\n"
		"in vec2 Position;\n"
		"in vec2 UV;\n"
		"in vec4 Color;\n"
		"out vec2 Frag_UV;\n"
		"out vec4 Frag_Color;\n"
		"void main()\n"
		"{\n"
		"	Frag_UV = UV;\n"
		"	Frag_Color = Color;\n"
		"	gl_Position = ProjMtx * vec4(Position.xy,0,1);\n"
		"}\n";

	const GLchar* fragment_shader =
		"#version 330\n"
		"uniform sampler2D Texture;\n"
		"in vec2 Frag_UV;\n"
		"in vec4 Frag_Color;\n"
		"out vec4 Out_Color;\n"
		"void main()\n"
		"{\n"
		"	Out_Color = Frag_Color * texture( Texture, Frag_UV.st);\n"
		"}\n";

	ShaderHandle = glCreateProgram();
	VertHandle = glCreateShader(GL_VERTEX_SHADER);
	FragHandle = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(VertHandle, 1, &vertex_shader, 0);
	glShaderSource(FragHandle, 1, &fragment_shader, 0);
	glCompileShader(VertHandle);
	glCompileShader(FragHandle);
	glAttachShader(ShaderHandle, VertHandle);
	glAttachShader(ShaderHandle, FragHandle);
	glLinkProgram(ShaderHandle);

	AttribLocationTex = glGetUniformLocation(ShaderHandle, "Texture");
	AttribLocationProjMtx = glGetUniformLocation(ShaderHandle, "ProjMtx");
	AttribLocationPosition = glGetAttribLocation(ShaderHandle, "Position");
	AttribLocationUV = glGetAttribLocation(ShaderHandle, "UV");
	AttribLocationColor = glGetAttribLocation(ShaderHandle, "Color");

	glGenBuffers(1, &VboHandle);
	glGenVertexArrays(1, &VaoHandle);
	glBindVertexArray(VaoHandle);
	glBindBuffer(GL_ARRAY_BUFFER, VboHandle);
	glEnableVertexAttribArray(AttribLocationPosition);
	glEnableVertexAttribArray(AttribLocationUV);
	glEnableVertexAttribArray(AttribLocationColor);

#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))
	glVertexAttribPointer(AttribLocationPosition, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid*) OFFSETOF(ImDrawVert, pos));
	glVertexAttribPointer(AttribLocationUV, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid*) OFFSETOF(ImDrawVert, uv));
	glVertexAttribPointer(AttribLocationColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(ImDrawVert), (GLvoid*) OFFSETOF(ImDrawVert, col));
#undef OFFSETOF
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	CreateFontsTexture();

	return true;
}

void ImGui_ImplGlfwGL3_RenderDrawLists(ImDrawData* draw_data)
{
	SingletonPointer<CImGUIManager> ImGUIManager;
	ImGUIManager->DrawCallback(draw_data);
}

char const * ImGui_ImplGlfwGL3_GetClipboardText()
{
	SingletonPointer<CImGUIManager> ImGUIManager;
	return ImGUIManager->Window->GetClipboardText().c_str();
}

void ImGui_ImplGlfwGL3_SetClipboardText(const char* text)
{
	SingletonPointer<CImGUIManager> ImGUIManager;
	ImGUIManager->Window->SetClipboardText(text);
}

bool CImGUIManager::Init(CWindow* window, bool install_callbacks)
{
	Window = window;

	ImGuiIO& io = ImGui::GetIO();
	io.KeyMap[ImGuiKey_Tab] = (int) EKey::Tab;
	io.KeyMap[ImGuiKey_LeftArrow] = (int) EKey::Left;
	io.KeyMap[ImGuiKey_RightArrow] = (int) EKey::Right;
	io.KeyMap[ImGuiKey_UpArrow] = (int) EKey::Up;
	io.KeyMap[ImGuiKey_DownArrow] = (int) EKey::Down;
	io.KeyMap[ImGuiKey_Home] = (int) EKey::Home;
	io.KeyMap[ImGuiKey_End] = (int) EKey::End;
	io.KeyMap[ImGuiKey_Delete] = (int) EKey::Delete;
	io.KeyMap[ImGuiKey_Backspace] = (int) EKey::Backspace;
	io.KeyMap[ImGuiKey_Enter] = (int) EKey::Return;
	io.KeyMap[ImGuiKey_Escape] = (int) EKey::Escape;
	io.KeyMap[ImGuiKey_A] = (int) EKey::A;
	io.KeyMap[ImGuiKey_C] = (int) EKey::C;
	io.KeyMap[ImGuiKey_V] = (int) EKey::V;
	io.KeyMap[ImGuiKey_X] = (int) EKey::X;
	io.KeyMap[ImGuiKey_Y] = (int) EKey::Y;
	io.KeyMap[ImGuiKey_Z] = (int) EKey::Z;

	io.RenderDrawListsFn = ImGui_ImplGlfwGL3_RenderDrawLists;
	io.SetClipboardTextFn = ImGui_ImplGlfwGL3_SetClipboardText;
	io.GetClipboardTextFn = ImGui_ImplGlfwGL3_GetClipboardText;

	io.IniFilename = nullptr;

	return true;
}

void CImGUIManager::Shutdown()
{
	if (VaoHandle) glDeleteVertexArrays(1, &VaoHandle);
	if (VboHandle) glDeleteBuffers(1, &VboHandle);
	VaoHandle = 0;
	VboHandle = 0;

	glDetachShader(ShaderHandle, VertHandle);
	glDeleteShader(VertHandle);
	VertHandle = 0;

	glDetachShader(ShaderHandle, FragHandle);
	glDeleteShader(FragHandle);
	FragHandle = 0;

	glDeleteProgram(ShaderHandle);
	ShaderHandle = 0;

	if (FontTexture)
	{
		glDeleteTextures(1, &FontTexture);
		ImGui::GetIO().Fonts->TexID = 0;
		FontTexture = 0;
	}
	ImGui::Shutdown();
}

void CImGUIManager::NewFrame()
{
	static int frame = 0;
	SingletonPointer<CTimeManager> TimeManager;

	if (! FontTexture)
		CreateDeviceObjects();

	ImGuiIO& io = ImGui::GetIO();

	// Setup display size (every frame to accommodate for window resizing)
	io.DisplaySize = ImVec2((float) Window->GetSize().X, (float) Window->GetSize().Y);

	// Setup time step
	double current_time = TimeManager->GetRunTime();
	io.DeltaTime = Time > 0.0 ? (float) (current_time - Time) : (float) (1.0f / 60.0f);
	Time = current_time;

	// Setup inputs
	// (we already got mouse wheel, keyboard keys & characters from glfw callbacks polled in glfwPollEvents())
	if (Window->IsFocused())
	{
		double mouse_x, mouse_y;
		mouse_x = Window->GetCursorLocation().X;
		mouse_y = Window->GetCursorLocation().Y;
		io.MousePos = ImVec2((float) mouse_x, (float) mouse_y);   // Mouse position, in pixels (set to -1,-1 if no mouse / on another screen, etc.)
	}
	else
	{
		io.MousePos = ImVec2(-1, -1);
	}

	for (int i = 0; i < 3; i++)
	{
		io.MouseDown[i] = MousePressed[i] || Window->IsMouseDown((SMouseEvent::EButton) i);    // If a mouse press event came, always pass it as "mouse held this frame", so we don't miss click-release events that are shorter than 1 frame.
		MousePressed[i] = false;
	}

	io.MouseWheel = MouseWheel;
	MouseWheel = 0;

	// Start the frame
	ImGui::NewFrame();
}

CImGUIManager::CImGUIManager()
{
	for (int i = 0; i < 3; ++ i)
		MousePressed[i] = false;
}
