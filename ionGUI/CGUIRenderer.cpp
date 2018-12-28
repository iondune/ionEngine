
#include "CGUIRenderer.h"
#include <ionGraphicsD3D11/CD3D11Implementation.h>
#include <ionGraphicsD3D11/CTexture.h>

#include "imgui_impl_dx11.h"


namespace ion
{

	bool CGUIRenderer::Init(CWindow * Window, IGraphicsImplementation * GraphicsImplementation)
	{
		Graphics::CD3D11Implementation * D3D11 = dynamic_cast<Graphics::CD3D11Implementation *>(GraphicsImplementation);

		ID3D11Device * Device = D3D11->GetDevice();
		ID3D11DeviceContext * DeviceContext = D3D11->GetImmediateContext();

		return ImGui_ImplDX11_Init(Device, DeviceContext);
	}

	void CGUIRenderer::Shutdown()
	{
		ImGui_ImplDX11_Shutdown();
	}

	void CGUIRenderer::NewFrame()
	{
		ImGui_ImplDX11_NewFrame();
	}

	void CGUIRenderer::Draw(ImDrawData * draw_data)
	{
		ImGui_ImplDX11_RenderDrawData(draw_data);
	}

}
