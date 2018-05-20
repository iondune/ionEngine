
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
			SwapChainDesc.BufferDesc.Height = Window->GetSize().X;
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
			SharedPointer<D3D11::CVertexBuffer> VertexBuffer = std::make_shared<D3D11::CVertexBuffer>();
			return VertexBuffer;
		}

		SharedPointer<IIndexBuffer> CD3D11Implementation::CreateIndexBuffer()
		{
			SharedPointer<D3D11::CIndexBuffer> IndexBuffer = std::make_shared<D3D11::CIndexBuffer>();
			return IndexBuffer;
		}

		SharedPointer<Graphics::IDepthBuffer> CD3D11Implementation::CreateDepthBuffer(vec2i const & Size)
		{
			SharedPointer<D3D11::CDepthBuffer> DepthBuffer = std::make_shared<D3D11::CDepthBuffer>(Size);
			return DepthBuffer;
		}

		Graphics::IDrawContext * CD3D11Implementation::CreateDrawContext()
		{
			return new Graphics::GL::CDrawContext();
		}

		SharedPointer<ITexture2D> CD3D11Implementation::CreateTexture2D(vec2i const & Size, ITexture::EMipMaps const MipMaps, ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type)
		{
			SharedPointer<GL::CTexture2D> Texture2D = std::make_shared<GL::CTexture2D>();

			Texture2D->TextureSize = Size;
			Texture2D->MipMaps = (MipMaps == ITexture::EMipMaps::True);

			switch (Type)
			{
			case ITexture::EInternalFormatType::Fix8:
			case ITexture::EInternalFormatType::Float16:
			case ITexture::EInternalFormatType::Float32:
			case ITexture::EInternalFormatType::Depth:
				Texture2D->IsInteger = false;
				break;

			case ITexture::EInternalFormatType::SignedInt8:
			case ITexture::EInternalFormatType::SignedInt16:
			case ITexture::EInternalFormatType::SignedInt32:
			case ITexture::EInternalFormatType::UnsignedInt8:
			case ITexture::EInternalFormatType::UnsignedInt16:
			case ITexture::EInternalFormatType::UnsignedInt32:
				Texture2D->IsInteger = true;
				Texture2D->MinFilter = ITexture::EFilter::Nearest;
				Texture2D->MipMapFilter = ITexture::EFilter::Nearest;
				break;
			}

			int Levels = 1;

			if (Texture2D->MipMaps)
			{
				Levels = (int) floor(log2((double) Max(Size.X, Size.Y)));
			}

			D3D11_TEXTURE2D_DESC Desc = {};
			Desc.Width = Size.X;
			Desc.Height = Size.Y;
			Desc.MipLevels = 0;
			Desc.ArraySize = 1;
			Desc.Format = DXGI_FORMAT_R8G8B8A8_UINT;
			Desc.SampleDesc.Count = 1;
			Desc.SampleDesc.Quality = 0;
			Desc.Usage = D3D11_USAGE_DEFAULT;
			Desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
			Desc.CPUAccessFlags = 0;
			Desc.MiscFlags = 0;

			ID3D11Texture2D * Handle = nullptr;
			CheckedDXCall( Device->CreateTexture2D( &Desc, NULL, &Handle ));

			return Texture2D;
		}

		SharedPointer<ITexture3D> CD3D11Implementation::CreateTexture3D(vec3i const & Size, ITexture::EMipMaps const MipMaps, ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type)
		{
			SharedPointer<GL::CTexture3D> Texture3D = std::make_shared<GL::CTexture3D>();

			Texture3D->TextureSize = Size;
			Texture3D->MipMaps = (MipMaps == ITexture::EMipMaps::True);

			switch (Type)
			{
			case ITexture::EInternalFormatType::Fix8:
			case ITexture::EInternalFormatType::Float16:
			case ITexture::EInternalFormatType::Float32:
			case ITexture::EInternalFormatType::Depth:
				Texture3D->IsInteger = false;
				break;

			case ITexture::EInternalFormatType::SignedInt8:
			case ITexture::EInternalFormatType::SignedInt16:
			case ITexture::EInternalFormatType::SignedInt32:
			case ITexture::EInternalFormatType::UnsignedInt8:
			case ITexture::EInternalFormatType::UnsignedInt16:
			case ITexture::EInternalFormatType::UnsignedInt32:
				Texture3D->IsInteger = true;
				Texture3D->MinFilter = ITexture::EFilter::Nearest;
				Texture3D->MipMapFilter = ITexture::EFilter::Nearest;
				break;
			}

			int Levels = 1;

			if (Texture3D->MipMaps)
			{
				Levels = (int) floor(log2((double) Max(Size.X, Size.Y, Size.Z)));
			}

			return Texture3D;
		}

		SharedPointer<ITexture2DArray> CD3D11Implementation::CreateTexture2DArray(vec3i const & Size, ITexture::EMipMaps const MipMaps, ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type)
		{
			SharedPointer<GL::CTexture2DArray> Texture2DArray = std::make_shared<GL::CTexture2DArray>();

			Texture2DArray->TextureSize = Size;
			Texture2DArray->MipMaps = (MipMaps == ITexture::EMipMaps::True);

			switch (Type)
			{
			case ITexture::EInternalFormatType::Fix8:
			case ITexture::EInternalFormatType::Float16:
			case ITexture::EInternalFormatType::Float32:
			case ITexture::EInternalFormatType::Depth:
				Texture2DArray->IsInteger = false;
				break;

			case ITexture::EInternalFormatType::SignedInt8:
			case ITexture::EInternalFormatType::SignedInt16:
			case ITexture::EInternalFormatType::SignedInt32:
			case ITexture::EInternalFormatType::UnsignedInt8:
			case ITexture::EInternalFormatType::UnsignedInt16:
			case ITexture::EInternalFormatType::UnsignedInt32:
				Texture2DArray->IsInteger = true;
				Texture2DArray->MinFilter = ITexture::EFilter::Nearest;
				Texture2DArray->MipMapFilter = ITexture::EFilter::Nearest;
				break;
			}

			int Levels = 1;

			if (Texture2DArray->MipMaps)
			{
				Levels = (int) floor(log2((double) Max(Size.X, Size.Y, Size.Z)));
			}

			return Texture2DArray;
		}

		SharedPointer<ITextureCubeMap> CD3D11Implementation::CreateTextureCubeMap(vec2i const & Size, ITexture::EMipMaps const MipMaps, ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type)
		{
			SharedPointer<GL::CTextureCubeMap> TextureCubeMap = std::make_shared<GL::CTextureCubeMap>();

			TextureCubeMap->TextureSize = Size;
			TextureCubeMap->MipMaps = (MipMaps == ITexture::EMipMaps::True);

			switch (Type)
			{
			case ITexture::EInternalFormatType::Fix8:
			case ITexture::EInternalFormatType::Float16:
			case ITexture::EInternalFormatType::Float32:
			case ITexture::EInternalFormatType::Depth:
				TextureCubeMap->IsInteger = false;
				break;

			case ITexture::EInternalFormatType::SignedInt8:
			case ITexture::EInternalFormatType::SignedInt16:
			case ITexture::EInternalFormatType::SignedInt32:
			case ITexture::EInternalFormatType::UnsignedInt8:
			case ITexture::EInternalFormatType::UnsignedInt16:
			case ITexture::EInternalFormatType::UnsignedInt32:
				TextureCubeMap->IsInteger = true;
				TextureCubeMap->MinFilter = ITexture::EFilter::Nearest;
				TextureCubeMap->MipMapFilter = ITexture::EFilter::Nearest;
				break;
			}

			int Levels = 1;

			if (TextureCubeMap->MipMaps)
			{
				Levels = (int) floor(log2((double) Max(Size.X, Size.Y)));
			}

			return TextureCubeMap;
		}

		SharedPointer<IGraphicsContext> CD3D11Implementation::GetWindowContext(CWindow * Window)
		{
			return MakeShared<GL::CGraphicsContext>(Window);
		}

	}
}
