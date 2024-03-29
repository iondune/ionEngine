
#include "CD3D11Implementation.h"
#include "Utilities.h"

#include "CVertexBuffer.h"
#include "CIndexBuffer.h"

#include "CVertexStage.h"
#include "CGeometryStage.h"
#include "CPixelStage.h"
#include "CShader.h"

#include "CTexture.h"
#include "CRenderTarget.h"
#include "CDepthBuffer.h"

#include "CGraphicsContext.h"
#include "CPipelineState.h"
#include "CDrawContext.h"

#include <ionWindow/CWindow.h>

#include <d3d11.h>
#include <d3d11_1.h>
#include <dxgi.h>
#include <d3dcompiler.h>

#include <DXGItype.h>  
#include <dxgi1_2.h>  
#include <dxgi1_3.h>  
#include <DXProgrammableCapture.h>  


namespace ion
{
	namespace Graphics
	{

		bool CD3D11Implementation::PostWindowCreationSetup(CWindow * Window)
		{
			DXGI_SWAP_CHAIN_DESC SwapChainDesc = {};
			SwapChainDesc.BufferDesc.Width = Window->GetSize().X;
			SwapChainDesc.BufferDesc.Height = Window->GetSize().Y;
			SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			SwapChainDesc.SampleDesc.Count = 1;
			SwapChainDesc.SampleDesc.Quality = 0;
			SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			SwapChainDesc.BufferCount = 1;
			SwapChainDesc.OutputWindow = static_cast<HWND>(Window->GetPlatformHandle());
			SwapChainDesc.Windowed = true;

			SwapChain = nullptr;
			Device = nullptr;
			ImmediateContext = nullptr;

			UINT CreateDeviceFlags = 0;
			CreateDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;

			HRESULT hr = D3D11CreateDeviceAndSwapChain(
				nullptr, D3D_DRIVER_TYPE_HARDWARE,
				NULL, CreateDeviceFlags,
				NULL, 0,
				D3D11_SDK_VERSION,
				& SwapChainDesc,
				& SwapChain,
				& Device,
				NULL,
				& ImmediateContext);

			if (! SUCCEEDED(hr))
			{
				switch (hr)
				{
				case DXGI_ERROR_SDK_COMPONENT_MISSING:
				{
					// Debug support might not be enabled - try to create without
					CreateDeviceFlags ^= D3D11_CREATE_DEVICE_DEBUG;

					Log::Info("D3D11 Device creation failed due to missing SDK component - trying again without Debug enabled.");

					CheckedDXCall( D3D11CreateDeviceAndSwapChain(
						nullptr, D3D_DRIVER_TYPE_HARDWARE,
						NULL, CreateDeviceFlags,
						NULL, 0,
						D3D11_SDK_VERSION,
						& SwapChainDesc,
						& SwapChain,
						& Device,
						NULL,
						& ImmediateContext) );
					break;
				}
				default:
					D3D11::PrintHRESULT(hr, "D3D11CreateDeviceAndSwapChain", __FILE__, __LINE__);
					break;
				}
			}

			if (! Device)
			{
				return false;
			}

			DebugDevice = nullptr;
			Device->QueryInterface(IID_PPV_ARGS(& DebugDevice));

			DXGIGetDebugInterface1(0, IID_PPV_ARGS(& GraphicsAnalysis));

			// Rasterizer Settings

			D3D11_RASTERIZER_DESC RasterizerDesc = {};
			RasterizerDesc.FillMode = D3D11_FILL_SOLID;
			RasterizerDesc.CullMode = D3D11_CULL_NONE;
			RasterizerDesc.FrontCounterClockwise = true;
			RasterizerDesc.DepthBias = 0;
			RasterizerDesc.SlopeScaledDepthBias = 0.f;
			RasterizerDesc.DepthBiasClamp = 0.f;
			RasterizerDesc.DepthClipEnable = true;
			RasterizerDesc.ScissorEnable = false;
			RasterizerDesc.MultisampleEnable = false;
			RasterizerDesc.AntialiasedLineEnable = false;

			ID3D11RasterizerState * RasterizerState = nullptr;
			CheckedDXCall( Device->CreateRasterizerState(& RasterizerDesc, & RasterizerState) );
			ImmediateContext->RSSetState(RasterizerState);

			CheckedDXCall( ImmediateContext->QueryInterface(IID_PPV_ARGS(& UserDefinedAnnotation)) );

			// Depth Settings

			D3D11_DEPTH_STENCIL_DESC DepthDesc;
			DepthDesc.DepthEnable                  = true;
			DepthDesc.DepthWriteMask               = D3D11_DEPTH_WRITE_MASK_ALL;
			DepthDesc.DepthFunc                    = D3D11_COMPARISON_LESS_EQUAL;
			DepthDesc.StencilEnable                = true;
			DepthDesc.StencilReadMask              = D3D11_DEFAULT_STENCIL_READ_MASK;
			DepthDesc.StencilWriteMask             = D3D11_DEFAULT_STENCIL_WRITE_MASK;
			DepthDesc.FrontFace.StencilFunc        = D3D11_COMPARISON_ALWAYS;
			DepthDesc.BackFace.StencilFunc         = D3D11_COMPARISON_ALWAYS;
			DepthDesc.FrontFace.StencilFailOp      = D3D11_STENCIL_OP_KEEP;
			DepthDesc.BackFace.StencilFailOp       = D3D11_STENCIL_OP_KEEP;
			DepthDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
			DepthDesc.BackFace.StencilDepthFailOp  = D3D11_STENCIL_OP_KEEP;
			DepthDesc.FrontFace.StencilPassOp      = D3D11_STENCIL_OP_KEEP;
			DepthDesc.BackFace.StencilPassOp       = D3D11_STENCIL_OP_KEEP;

			ID3D11DepthStencilState * DepthStencilState = nullptr;
			CheckedDXCall( Device->CreateDepthStencilState(& DepthDesc, & DepthStencilState) );
			ImmediateContext->OMSetDepthStencilState(DepthStencilState, 1);

			return true;
		}

		bool CD3D11Implementation::OnWindowSwap(CWindow * Window)
		{
			SwapChain->Present(0, 0);
			return false;
		}

		void CD3D11Implementation::OnShutdown()
		{
			if (DebugDevice)
			{
				DebugDevice->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
				DebugDevice->Release();
				DebugDevice = nullptr;
			}
		}

		SharedPointer<IVertexStage> CD3D11Implementation::CreateVertexShaderFromSource(string const & Source, string const & SourceName, vector<string> const & IncludeDirectories, vector<string> * outErrorsAndWarnings)
		{
			return std::shared_ptr<D3D11::CVertexStage>(D3D11::CVertexStage::Compile(Device, Source, SourceName, IncludeDirectories, outErrorsAndWarnings));
		}

		SharedPointer<IGeometryStage> CD3D11Implementation::CreateGeometryShaderFromSource(string const & Source, string const & SourceName, vector<string> const & IncludeDirectories, vector<string> * outErrorsAndWarnings)
		{
			return std::shared_ptr<D3D11::CGeometryStage>(D3D11::CGeometryStage::Compile(Device, Source, SourceName, IncludeDirectories, outErrorsAndWarnings));
		}

		SharedPointer<IPixelStage> CD3D11Implementation::CreatePixelShaderFromSource(string const & Source, string const & SourceName, vector<string> const & IncludeDirectories, vector<string> * outErrorsAndWarnings)
		{
			return std::shared_ptr<D3D11::CPixelStage>(D3D11::CPixelStage::Compile(Device, Source, SourceName, IncludeDirectories, outErrorsAndWarnings));
		}

		SharedPointer<IShader> CD3D11Implementation::CreateShaderProgram()
		{
			SharedPointer<D3D11::CShader> ShaderProgram = std::make_shared<D3D11::CShader>(Device, ImmediateContext);
			return ShaderProgram;
		}

		SharedPointer<IVertexBuffer> CD3D11Implementation::CreateVertexBuffer()
		{
			return std::make_shared<D3D11::CVertexBuffer>(Device);
		}

		SharedPointer<IInstanceBuffer> CD3D11Implementation::CreateInstanceBuffer()
		{
			return std::make_shared<D3D11::CInstanceBuffer>(Device);
		}

		SharedPointer<IIndexBuffer> CD3D11Implementation::CreateIndexBuffer()
		{
			return std::make_shared<D3D11::CIndexBuffer>(Device);
		}

		SharedPointer<Graphics::IDepthBuffer> CD3D11Implementation::CreateDepthBuffer(vec2i const & Size)
		{
			return std::make_shared<D3D11::CDepthBuffer>(Device, Size);
		}

		Graphics::IDrawContext * CD3D11Implementation::GetDrawContext()
		{
			if (DrawContext == nullptr)
			{
				DrawContext = new D3D11::CDrawContext(Device, ImmediateContext);
			}

			return DrawContext;
		}

		SharedPointer<ITexture2D> CD3D11Implementation::CreateTexture2D(vec2i const & Size, ITexture::EMipMaps const MipMaps, ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type)
		{
			return std::make_shared<D3D11::CTexture2D>(Device, ImmediateContext, Size, MipMaps, Components, Type);
		}

		SharedPointer<ITexture3D> CD3D11Implementation::CreateTexture3D(vec3i const & Size, ITexture::EMipMaps const MipMaps, ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type)
		{
			return nullptr;//std::make_shared<D3D11::CTexture3D>();
		}

		SharedPointer<ITexture2DArray> CD3D11Implementation::CreateTexture2DArray(vec3i const & Size, ITexture::EMipMaps const MipMaps, ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type)
		{
			return nullptr;//std::make_shared<D3D11::CTexture2DArray>();
		}

		SharedPointer<ITextureCubeMap> CD3D11Implementation::CreateTextureCubeMap(vec2i const & Size, ITexture::EMipMaps const MipMaps, ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type)
		{
			return nullptr;//std::make_shared<D3D11::CTextureCubeMap>();
		}

		SharedPointer<IGraphicsContext> CD3D11Implementation::GetWindowContext(CWindow * Window)
		{
			return std::make_shared<D3D11::CGraphicsContext>(Device, ImmediateContext, SwapChain, Window);
		}

		IDXGISwapChain * CD3D11Implementation::GetSwapChain()
		{
			return SwapChain;
		}

		ID3D11Device * CD3D11Implementation::GetDevice()
		{
			return Device;
		}

		ID3D11DeviceContext * CD3D11Implementation::GetImmediateContext()
		{
			return ImmediateContext;
		}

		ID3D11Debug * CD3D11Implementation::GetDebugDevice()
		{
			return DebugDevice;
		}

		void CD3D11Implementation::DiagnosticCaptureBegin()
		{
			if (GraphicsAnalysis)
			{
				GraphicsAnalysis->BeginCapture();
			}
		}

		void CD3D11Implementation::DiagnosticCaptureEnd()
		{
			if (GraphicsAnalysis)
			{
				GraphicsAnalysis->EndCapture();
			}
		}

		void CD3D11Implementation::AnnotateBeginEvent(string const & eventName)
		{
			if (UserDefinedAnnotation)
			{
				std::wstring temp = std::wstring(eventName.begin(), eventName.end());
				UserDefinedAnnotation->BeginEvent(temp.c_str());
				EventStack.push_back(eventName);
			}
		}

		void CD3D11Implementation::AnnotateEndEvent(string const & eventName)
		{
			if (UserDefinedAnnotation)
			{
				UserDefinedAnnotation->EndEvent();

				string const stackTop = EventStack.back();
				EventStack.pop_back();

				if (stackTop != eventName)
				{
					Log::Warn("CD3D11Implementation: Popped '%s' from the event stack, but ended '%s' event.");
				}
			}
		}

	}
}
