
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionGraphics.h>
#include <ionWindow.h>

#include <D3D11.h>
#include <DXGI.h>


namespace ion
{
	namespace Graphics
	{
		namespace D3D11
		{
			
			class CRenderTarget : public virtual IRenderTarget
			{

			public:

				CRenderTarget(ID3D11Device * Device);
				CRenderTarget(ID3D11Device * Device, IDXGISwapChain * SwapChain, vec2i const & Size);

				void ClearColor();
				void ClearDepth();
				void ClearColorAndDepth();

				void SetClearColor(color4f const & Color);

				virtual CImage * ReadImage();

				virtual void Bind();
				void Rebind();
				virtual IRenderTarget * GetCurrentlyBound();

				vec2i Size;
				color4f Color;
				vec2i ViewportMin;
				vec2i ViewportMax;
				bool SpecifiedViewport = false;

				virtual void SetViewport(vec2i const & Min, vec2i const & Max);
				virtual void ClearViewport();

				static CRenderTarget * CurrentlyBound;

				ID3D11Device * Device = nullptr;
				ID3D11DeviceContext * ImmediateContext = nullptr;

				vector<ID3D11RenderTargetView *> RenderTargetViews;
				ID3D11DepthStencilView * DepthStencilView = nullptr;

			};

		}
	}
}
