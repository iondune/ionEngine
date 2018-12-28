
#pragma once

#include <ionCore.h>
#include <ionMath.h>

#include "Enums.h"
#include "IShader.h"
#include "IVertexBuffer.h"
#include "IIndexBuffer.h"
#include "ITexture.h"
#include "IGraphicsContext.h"
#include "IDrawContext.h"


namespace ion
{

	class CWindow;

	//! \ingroup ionGraphics
	class IGraphicsImplementation
	{

	public:

		virtual void PreWindowCreationSetup() = 0;
		virtual void PostWindowCreationSetup(CWindow * Window) = 0;
		virtual bool OnWindowSwap(CWindow * Window) = 0;

		virtual SharedPointer<Graphics::IVertexStage> CreateVertexShaderFromSource(string const & Source, string const & SourceName, vector<string> const & IncludeDirectories) = 0;
		virtual SharedPointer<Graphics::IGeometryStage> CreateGeometryShaderFromSource(string const & Source, string const & SourceName, vector<string> const & IncludeDirectories) = 0;
		virtual SharedPointer<Graphics::IPixelStage> CreatePixelShaderFromSource(string const & Source, string const & SourceName, vector<string> const & IncludeDirectories) = 0;

		virtual SharedPointer<Graphics::IShader> CreateShaderProgram() = 0;

		virtual SharedPointer<Graphics::IVertexBuffer> CreateVertexBuffer() = 0;
		virtual SharedPointer<Graphics::IInstanceBuffer> CreateInstanceBuffer() = 0;
		virtual SharedPointer<Graphics::IIndexBuffer> CreateIndexBuffer() = 0;

		virtual SharedPointer<Graphics::IDepthBuffer> CreateDepthBuffer(vec2i const & Size) = 0;

		virtual Graphics::IDrawContext * GetDrawContext() = 0;

		virtual SharedPointer<Graphics::ITexture2D> CreateTexture2D(vec2i const & Size, Graphics::ITexture::EMipMaps const MipMaps, Graphics::ITexture::EFormatComponents const Components, Graphics::ITexture::EInternalFormatType const Type) = 0;
		virtual SharedPointer<Graphics::ITexture3D> CreateTexture3D(vec3i const & Size, Graphics::ITexture::EMipMaps const MipMaps, Graphics::ITexture::EFormatComponents const Components, Graphics::ITexture::EInternalFormatType const Type) = 0;
		virtual SharedPointer<Graphics::ITexture2DArray> CreateTexture2DArray(vec3i const & Size, Graphics::ITexture::EMipMaps const MipMaps, Graphics::ITexture::EFormatComponents const Components, Graphics::ITexture::EInternalFormatType const Type) = 0;
		virtual SharedPointer<Graphics::ITextureCubeMap> CreateTextureCubeMap(vec2i const & Size, Graphics::ITexture::EMipMaps const MipMaps, Graphics::ITexture::EFormatComponents const Components, Graphics::ITexture::EInternalFormatType const Type) = 0;

		virtual SharedPointer<Graphics::IGraphicsContext> GetWindowContext(CWindow * Window) = 0;

		virtual void DiagnosticCaptureBegin() = 0;
		virtual void DiagnosticCaptureEnd() = 0;

	};

}
