
#include "CD3D11Implementation.h"
#include "Utilities.h"

#include "CVertexBuffer.h"
#include "CIndexBuffer.h"

#include "CVertexStage.h"
#include "CGeometryStage.h"
#include "CPixelStage.h"
#include "CShaderProgram.h"

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

			D3D11CreateDeviceAndSwapChain(
				nullptr, D3D_DRIVER_TYPE_HARDWARE,
				NULL, CreateDeviceFlags,
				NULL, 0,
				D3D11_SDK_VERSION,
				& SwapChainDesc,
				& SwapChain,
				& Device,
				NULL,
				& ImmediateContext);

			DebugDevice = nullptr;
			Device->QueryInterface(IID_PPV_ARGS(&DebugDevice));

		}

		bool CD3D11Implementation::OnWindowSwap(CWindow * Window)
		{
			SwapChain->Present(0, 0);
			return false;
		}

		SharedPointer<IVertexStage> CD3D11Implementation::CreateVertexShaderFromSource(string const & Source)
		{
			return std::make_shared<D3D11::CVertexStage>(Device, Source);
		}

		SharedPointer<IGeometryStage> CD3D11Implementation::CreateGeometryShaderFromSource(string const & Source)
		{
			return std::make_shared<D3D11::CGeometryStage>(Device, Source);
		}

		SharedPointer<IPixelStage> CD3D11Implementation::CreatePixelShaderFromSource(string const & Source)
		{
			return std::make_shared<D3D11::CPixelStage>(Device, Source);
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
			SharedPointer<D3D11::CDepthBuffer> DepthBuffer = std::make_shared<D3D11::CDepthBuffer>(Size);
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

	}
}
