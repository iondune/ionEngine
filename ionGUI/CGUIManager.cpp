
#include "CGUIManager.h"
#include <ionGraphicsGL/CTexture.h>
#include <glad/glad.h>


namespace ion
{

	// This is the main rendering function that you have to implement and provide to ImGui (via setting up 'RenderDrawListsFn' in the ImGuiIO structure)
	// If text or lines are blurry when integrating ImGui in your engine:
	// - in your Render function, try translating your projection matrix by (0.5f,0.5f) or (0.375f,0.375f)
	void CGUIManager::DrawCallback(ImDrawData* draw_data)
	{
		Window->MakeContextCurrent();


		// Avoid rendering when minimized, scale coordinates for retina displays (screen coordinates != framebuffer coordinates)
		ImGuiIO& io = ImGui::GetIO();
		int fb_width = (int) (io.DisplaySize.x * io.DisplayFramebufferScale.x);
		int fb_height = (int) (io.DisplaySize.y * io.DisplayFramebufferScale.y);
		if (fb_width == 0 || fb_height == 0)
			return;
		draw_data->ScaleClipRects(io.DisplayFramebufferScale);

		// Backup GL state
		GLint last_program; glGetIntegerv(GL_CURRENT_PROGRAM, &last_program);
		GLint last_texture; glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
		GLint last_array_buffer; glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &last_array_buffer);
		GLint last_element_array_buffer; glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &last_element_array_buffer);
		GLint last_vertex_array; glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &last_vertex_array);
		GLint last_blend_src; glGetIntegerv(GL_BLEND_SRC, &last_blend_src);
		GLint last_blend_dst; glGetIntegerv(GL_BLEND_DST, &last_blend_dst);
		GLint last_blend_equation_rgb; glGetIntegerv(GL_BLEND_EQUATION_RGB, &last_blend_equation_rgb);
		GLint last_blend_equation_alpha; glGetIntegerv(GL_BLEND_EQUATION_ALPHA, &last_blend_equation_alpha);
		GLint last_viewport[4]; glGetIntegerv(GL_VIEWPORT, last_viewport);
		GLboolean last_enable_blend = glIsEnabled(GL_BLEND);
		GLboolean last_enable_cull_face = glIsEnabled(GL_CULL_FACE);
		GLboolean last_enable_depth_test = glIsEnabled(GL_DEPTH_TEST);
		GLboolean last_enable_scissor_test = glIsEnabled(GL_SCISSOR_TEST);

		// Setup render state: alpha-blending enabled, no face culling, no depth testing, scissor enabled
		glEnable(GL_BLEND);
		glBlendEquation(GL_FUNC_ADD);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_SCISSOR_TEST);
		glActiveTexture(GL_TEXTURE0);

		// Setup viewport, orthographic projection matrix
		glViewport(0, 0, (GLsizei) fb_width, (GLsizei) fb_height);
		const float ortho_projection[4][4] =
		{
			{ 2.0f / io.DisplaySize.x, 0.0f,                   0.0f, 0.0f },
			{ 0.0f,                  2.0f / -io.DisplaySize.y, 0.0f, 0.0f },
			{ 0.0f,                  0.0f,                  -1.0f, 0.0f },
			{ -1.0f,                  1.0f,                   0.0f, 1.0f },
		};
		glUseProgram(ShaderHandle);
		glUniform1i(AttribLocationTex, 0);
		glUniformMatrix4fv(AttribLocationProjMtx, 1, GL_FALSE, &ortho_projection[0][0]);
		glBindVertexArray(VaoHandle);

		for (int n = 0; n < draw_data->CmdListsCount; n++)
		{
			const ImDrawList* cmd_list = draw_data->CmdLists[n];
			const ImDrawIdx* idx_buffer_offset = 0;

			glBindBuffer(GL_ARRAY_BUFFER, VboHandle);
			glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr) cmd_list->VtxBuffer.size() * sizeof(ImDrawVert), (GLvoid*) &cmd_list->VtxBuffer.front(), GL_STREAM_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementsHandle);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr) cmd_list->IdxBuffer.size() * sizeof(ImDrawIdx), (GLvoid*) &cmd_list->IdxBuffer.front(), GL_STREAM_DRAW);

			for (const ImDrawCmd* pcmd = cmd_list->CmdBuffer.begin(); pcmd != cmd_list->CmdBuffer.end(); pcmd++)
			{
				if (pcmd->UserCallback)
				{
					pcmd->UserCallback(cmd_list, pcmd);
				}
				else
				{
					glBindTexture(GL_TEXTURE_2D, (GLuint) (intptr_t) pcmd->TextureId);
					glScissor((int) pcmd->ClipRect.x, (int) (fb_height - pcmd->ClipRect.w), (int) (pcmd->ClipRect.z - pcmd->ClipRect.x), (int) (pcmd->ClipRect.w - pcmd->ClipRect.y));
					glDrawElements(GL_TRIANGLES, (GLsizei) pcmd->ElemCount, sizeof(ImDrawIdx) == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, idx_buffer_offset);
				}
				idx_buffer_offset += pcmd->ElemCount;
			}
		}

		// Restore modified GL state
		glUseProgram(last_program);
		glBindTexture(GL_TEXTURE_2D, last_texture);
		glBindVertexArray(last_vertex_array);
		glBindBuffer(GL_ARRAY_BUFFER, last_array_buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, last_element_array_buffer);
		glBlendEquationSeparate(last_blend_equation_rgb, last_blend_equation_alpha);
		glBlendFunc(last_blend_src, last_blend_dst);
		if (last_enable_blend) glEnable(GL_BLEND); else glDisable(GL_BLEND);
		if (last_enable_cull_face) glEnable(GL_CULL_FACE); else glDisable(GL_CULL_FACE);
		if (last_enable_depth_test) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST);
		if (last_enable_scissor_test) glEnable(GL_SCISSOR_TEST); else glDisable(GL_SCISSOR_TEST);
		glViewport(last_viewport[0], last_viewport[1], (GLsizei) last_viewport[2], (GLsizei) last_viewport[3]);
	}

	void CGUIManager::OnEvent(IEvent & Event)
	{
		ImGuiIO& io = ImGui::GetIO();

		if (InstanceOf<SKeyboardEvent>(Event))
		{
			SKeyboardEvent KeyboardEvent = As<SKeyboardEvent>(Event);

			if (IO.WantCaptureKeyboard)
			{
				Event.Block();
			}

			io.KeysDown[(int) KeyboardEvent.Key] = KeyboardEvent.Pressed;

			// Hack/workaround to make KP enter work like enter
			// Will cause problems if regular Enter and KP Enter are pressed simultaneously
			// Don't do that
			if (KeyboardEvent.Key == EKey::KeyPadEnter)
			{
				io.KeysDown[(int) EKey::Enter] = KeyboardEvent.Pressed;
			}

			io.KeyCtrl = Window->IsKeyDown(EKey::LeftControl) || Window->IsKeyDown(EKey::RightControl);
			io.KeyShift = Window->IsKeyDown(EKey::LeftShift) || Window->IsKeyDown(EKey::RightShift);
			io.KeyAlt = Window->IsKeyDown(EKey::LeftAlt) || Window->IsKeyDown(EKey::RightAlt);
		}
		else if (InstanceOf<SMouseEvent>(Event))
		{
			SMouseEvent MouseEvent = As<SMouseEvent>(Event);

			if (IO.WantCaptureMouse)
			{
				Event.Block();
			}

			switch (MouseEvent.Type)
			{
			case SMouseEvent::EType::Click:
				MouseHeld[(int) MouseEvent.Button] = MouseEvent.Pressed;
				if (MouseEvent.Pressed)
				{
					MouseWasPressed[(int) MouseEvent.Button] = MouseEvent.Pressed;
				}
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
			if (CharacterEvent.C > 0)
				io.AddInputCharacter(CharacterEvent.C);
		}
	}

	void CGUIManager::CreateFontsTexture()
	{
		ImGuiIO& io = ImGui::GetIO();

		unsigned char* pixels;
		int width, height;
		io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

		GLint last_texture;
		glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
		glGenTextures(1, &FontTexture);
		glBindTexture(GL_TEXTURE_2D, FontTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

		io.Fonts->TexID = (void *) (intptr_t) FontTexture;

		glBindTexture(GL_TEXTURE_2D, last_texture);
	}

	void CGUIManager::AddFontFromFile(string const & FileName, float const Size)
	{
		ImGuiIO& io = ImGui::GetIO();
		ImFont* my_font = io.Fonts->AddFontFromFileTTF(FileName.c_str(), Size);
	}

	ImTextureID CGUIManager::GetTextureID(SharedPointer<Graphics::ITexture2D> const Texture)
	{
		SharedPointer<Graphics::GL::CTexture const> TextureImplementation = std::dynamic_pointer_cast<Graphics::GL::CTexture const>(Texture);
		return  (void *) (intptr_t) TextureImplementation->Handle;
	}

	bool CGUIManager::CreateDeviceObjects()
	{
		Window->MakeContextCurrent();

		// Backup GL state
		GLint last_texture, last_array_buffer, last_vertex_array;
		glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
		glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &last_array_buffer);
		glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &last_vertex_array);

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
		glGenBuffers(1, &ElementsHandle);

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

		CreateFontsTexture();

		// Restore modified GL state
		glBindTexture(GL_TEXTURE_2D, last_texture);
		glBindBuffer(GL_ARRAY_BUFFER, last_array_buffer);
		glBindVertexArray(last_vertex_array);

		return true;
	}

	void ImGui_ImplGlfwGL3_RenderDrawLists(ImDrawData * draw_data)
	{
		SingletonPointer<CGUIManager> ImGUIManager;
		ImGUIManager->DrawCallback(draw_data);
	}

	char const * ImGui_ImplGlfwGL3_GetClipboardText(void * user_data)
	{
		SingletonPointer<CGUIManager> ImGUIManager;
		return ImGUIManager->Window->GetClipboardText().c_str();
	}

	void ImGui_ImplGlfwGL3_SetClipboardText(void * user_data, char const * text)
	{
		SingletonPointer<CGUIManager> ImGUIManager;
		ImGUIManager->Window->SetClipboardText(text);
	}

	bool CGUIManager::Init(CWindow* window, float const DefaultFontSize)
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
		io.KeyMap[ImGuiKey_Enter] = (int) EKey::Enter;
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

		io.Fonts->AddFontFromFileTTF((string(ION_PROJECT_BASE_DIRECTORY) + "Fonts/Roboto-Regular.ttf").c_str(), DefaultFontSize);

		return true;
	}

	void CGUIManager::Shutdown()
	{
		Window->MakeContextCurrent();

		if (VaoHandle) glDeleteVertexArrays(1, &VaoHandle);
		if (VboHandle) glDeleteBuffers(1, &VboHandle);
		if (ElementsHandle) glDeleteBuffers(1, &ElementsHandle);
		VaoHandle = VboHandle = ElementsHandle = 0;

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

	void CGUIManager::NewFrame()
	{
		static int frame = 0;
		SingletonPointer<CTimeManager> TimeManager;

		if (! FontTexture)
			CreateDeviceObjects();

		ImGuiIO& io = ImGui::GetIO();

		// Setup display size (every frame to accommodate for window resizing)
		int w = Window->GetSize().X, h = Window->GetSize().Y;
		int display_w = Window->GetFrameBufferSize().X, display_h = Window->GetFrameBufferSize().Y;
		io.DisplaySize = ImVec2((float) w, (float) h);
		io.DisplayFramebufferScale = ImVec2(w > 0 ? ((float) display_w / w) : 0, h > 0 ? ((float) display_h / h) : 0);

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
			io.MouseDown[i] = MouseWasPressed[i] || MouseHeld[i];    // If a mouse press event came, always pass it as "mouse held this frame", so we don't miss click-release events that are shorter than 1 frame.
			MouseWasPressed[i] = false;
		}

		io.MouseWheel = MouseWheel;
		MouseWheel = 0;

		// Start the frame
		ImGui::NewFrame();
	}

void CGUIManager::Draw()
{
	ImGui::SetNextWindowPos(ImVec2(-1000, -1000));
	ImGui::SetNextWindowSize(ImVec2(100000, 100000));
	if (ImGui::Begin("GlobalScreen", nullptr, ImVec2(0, 0), 0.0f,
		ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs))
	{
		ImDrawList * DrawList = ImGui::GetWindowDrawList();

		for (auto Text : TextQueue)
		{
			uint Red = Text.Color.Red;
			uint Green = Text.Color.Green;
			uint Blue = Text.Color.Blue;
			DrawList->AddText(ImVec2((float) Text.Position.X, (float) Text.Position.Y), (0xFF000000) | (Blue << 16) | (Green << 8) | (Red), Text.Text.c_str());
		}
		TextQueue.clear();

		ImGui::End();
	}
	ImGui::Render();
}

void CGUIManager::TextUnformatted(vec2i const & Position, color3i const & Color, string const & Text)
{
	SDrawText Draw;
	Draw.Text = Text;
	Draw.Position = Position;
	Draw.Color = Color;

	TextQueue.push_back(Draw);
}

	CGUIManager::CGUIManager()
	{
		for (int i = 0; i < 3; ++ i)
		{
			MouseWasPressed[i] = false;
			MouseHeld[i] = false;
		}
	}

}
