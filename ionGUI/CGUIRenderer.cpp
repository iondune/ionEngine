
#include "CGUIRenderer.h"

#include "imgui_impl_opengl3.h"


namespace ion
{

	bool CGUIRenderer::Init(CWindow * Window)
	{
		return ImGui_ImplOpenGL3_Init("#version 330");
	}

	void CGUIRenderer::Shutdown()
	{
		ImGui_ImplOpenGL3_Shutdown();
	}

	void CGUIRenderer::NewFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
	}

	void CGUIRenderer::Draw(ImDrawData * draw_data)
	{
		ImGui_ImplOpenGL3_RenderDrawData(draw_data);
	}

}
