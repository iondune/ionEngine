
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
#include <dxgi.h>
#include <d3dcompiler.h>

#include <DXGItype.h>  
#include <dxgi1_2.h>  
#include <dxgi1_3.h>  
#include <DXProgrammableCapture.h>  

#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>


namespace ion
{
	namespace Graphics
	{

		void CD3D11Implementation::PreWindowCreationSetup()
		{
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		}

		void CD3D11Implementation::PostWindowCreationSetup(CWindow * Window)
		{
			DXGI_SWAP_CHAIN_DESC SwapChainDesc = {};
			SwapChainDesc.BufferDesc.Width = Window->GetSize().X;
			SwapChainDesc.BufferDesc.Height = Window->GetSize().Y;
			SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			SwapChainDesc.SampleDesc.Count = 1;
			SwapChainDesc.SampleDesc.Quality = 0;
			SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			SwapChainDesc.BufferCount = 1;
			SwapChainDesc.OutputWindow = glfwGetWin32Window(Window->GetHandle());
			SwapChainDesc.Windowed = true;

			SwapChain = nullptr;
			Device = nullptr;
			ImmediateContext = nullptr;

			UINT CreateDeviceFlags = 0;
#ifdef ION_CONFIG_DEBUG
			CreateDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

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
		}

		bool CD3D11Implementation::OnWindowSwap(CWindow * Window)
		{
			SwapChain->Present(0, 0);
			return false;
		}

		SharedPointer<IVertexStage> CD3D11Implementation::CreateVertexShaderFromSource(string const & Source, string const & SourceName, vector<string> const & IncludeDirectories)
		{
			return std::shared_ptr<D3D11::CVertexStage>(D3D11::CVertexStage::Compile(Device, Source, SourceName, IncludeDirectories));
		}

		SharedPointer<IGeometryStage> CD3D11Implementation::CreateGeometryShaderFromSource(string const & Source, string const & SourceName, vector<string> const & IncludeDirectories)
		{
			return std::shared_ptr<D3D11::CGeometryStage>(D3D11::CGeometryStage::Compile(Device, Source, SourceName, IncludeDirectories));
		}

		SharedPointer<IPixelStage> CD3D11Implementation::CreatePixelShaderFromSource(string const & Source, string const & SourceName, vector<string> const & IncludeDirectories)
		{
			return std::shared_ptr<D3D11::CPixelStage>(D3D11::CPixelStage::Compile(Device, Source, SourceName, IncludeDirectories));
		}

		SharedPointer<IShader> CD3D11Implementation::CreateShaderProgram()
		{
			SharedPointer<D3D11::CShader> ShaderProgram = std::make_shared<D3D11::CShader>();
			return ShaderProgram;
		}

		SharedPointer<IVertexBuffer> CD3D11Implementation::CreateVertexBuffer()
		{
			SharedPointer<D3D11::CVertexBuffer> VertexBuffer = std::make_shared<D3D11::CVertexBuffer>(Device);
			return VertexBuffer;
		}

		SharedPointer<IIndexBuffer> CD3D11Implementation::CreateIndexBuffer()
		{
			SharedPointer<D3D11::CIndexBuffer> IndexBuffer = std::make_shared<D3D11::CIndexBuffer>(Device);
			return IndexBuffer;
		}

		SharedPointer<Graphics::IDepthBuffer> CD3D11Implementation::CreateDepthBuffer(vec2i const & Size)
		{
			SharedPointer<D3D11::CDepthBuffer> DepthBuffer = std::make_shared<D3D11::CDepthBuffer>(Device, Size);
			return DepthBuffer;
		}

		Graphics::IDrawContext * CD3D11Implementation::CreateDrawContext()
		{
			return new Graphics::D3D11::CDrawContext();
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

	}
}
