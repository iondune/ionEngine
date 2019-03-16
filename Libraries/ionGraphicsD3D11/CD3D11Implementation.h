
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionGraphics.h>


struct IDXGISwapChain;
struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11Debug;
struct IDXGraphicsAnalysis;

namespace ion
{
	namespace Graphics
	{

		namespace D3D11
		{
			class CDrawContext;
		}

		class CD3D11Implementation : public IGraphicsImplementation
		{

		public:

			void PostWindowCreationSetup(CWindow * Window);
			bool OnWindowSwap(CWindow * Window);
			void OnShutdown();

			SharedPointer<IVertexStage> CreateVertexShaderFromSource(string const & Source, string const & SourceName, vector<string> const & IncludeDirectories, vector<string> * outErrorsAndWarnings);
			SharedPointer<IGeometryStage> CreateGeometryShaderFromSource(string const & Source, string const & SourceName, vector<string> const & IncludeDirectories, vector<string> * outErrorsAndWarnings);
			SharedPointer<IPixelStage> CreatePixelShaderFromSource(string const & Source, string const & SourceName, vector<string> const & IncludeDirectories, vector<string> * outErrorsAndWarnings);

			SharedPointer<IShader> CreateShaderProgram();

			SharedPointer<IVertexBuffer> CreateVertexBuffer();
			SharedPointer<IInstanceBuffer> CreateInstanceBuffer();
			SharedPointer<IIndexBuffer> CreateIndexBuffer();

			SharedPointer<IDepthBuffer> CreateDepthBuffer(vec2i const & Size);

			IDrawContext * GetDrawContext();

			SharedPointer<ITexture2D> CreateTexture2D(vec2i const & Size, ITexture::EMipMaps const MipMaps, ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type);
			SharedPointer<ITexture3D> CreateTexture3D(vec3i const & Size, ITexture::EMipMaps const MipMaps, ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type);
			SharedPointer<ITexture2DArray> CreateTexture2DArray(vec3i const & Size, ITexture::EMipMaps const MipMaps, ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type);
			SharedPointer<ITextureCubeMap> CreateTextureCubeMap(vec2i const & Size, ITexture::EMipMaps const MipMaps, ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type);

			SharedPointer<IGraphicsContext> GetWindowContext(CWindow * Window);

			IDXGISwapChain * GetSwapChain();
			ID3D11Device * GetDevice();
			ID3D11DeviceContext * GetImmediateContext();
			ID3D11Debug * GetDebugDevice();

			void UseReverseDepth(bool const reverseDepth = true) {}
			void DiagnosticCaptureBegin();
			void DiagnosticCaptureEnd();

		protected:

			bool ReverseDepth = false;

			IDXGISwapChain * SwapChain = nullptr;
			ID3D11Device * Device = nullptr;
			ID3D11DeviceContext * ImmediateContext = nullptr;
			ID3D11Debug * DebugDevice = nullptr;

			IDXGraphicsAnalysis * GraphicsAnalysis;

			D3D11::CDrawContext * DrawContext = nullptr;

		};
	}
}
