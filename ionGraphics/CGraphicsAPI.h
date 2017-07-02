
#pragma once

#include <ionCore.h>
#include <ionMath.h>

#include "Enums.h"
#include "IShaderProgram.h"
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
		virtual void PostWindowCreationSetup() = 0;

		virtual SharedPointer<Graphics::IVertexShader> CreateVertexShaderFromSource(string const & Source) = 0;
		virtual SharedPointer<Graphics::IGeometryShader> CreateGeometryShaderFromSource(string const & Source) = 0;
		virtual SharedPointer<Graphics::IPixelShader> CreatePixelShaderFromSource(string const & Source) = 0;

		virtual SharedPointer<Graphics::IShaderProgram> CreateShaderProgram() = 0;

		virtual SharedPointer<Graphics::IVertexBuffer> CreateVertexBuffer() = 0;
		virtual SharedPointer<Graphics::IIndexBuffer> CreateIndexBuffer() = 0;

		virtual SharedPointer<Graphics::IDepthBuffer> CreateDepthBuffer(vec2i const & Size) = 0;

		virtual Graphics::IDrawContext * CreateDrawContext() = 0;

		virtual SharedPointer<Graphics::ITexture2D> CreateTexture2D(vec2i const & Size, Graphics::ITexture::EMipMaps const MipMaps, Graphics::ITexture::EFormatComponents const Components, Graphics::ITexture::EInternalFormatType const Type) = 0;
		virtual SharedPointer<Graphics::ITexture3D> CreateTexture3D(vec3i const & Size, Graphics::ITexture::EMipMaps const MipMaps, Graphics::ITexture::EFormatComponents const Components, Graphics::ITexture::EInternalFormatType const Type) = 0;
		virtual SharedPointer<Graphics::ITexture2DArray> CreateTexture2DArray(vec3i const & Size, Graphics::ITexture::EMipMaps const MipMaps, Graphics::ITexture::EFormatComponents const Components, Graphics::ITexture::EInternalFormatType const Type) = 0;
		virtual SharedPointer<Graphics::ITextureCubeMap> CreateTextureCubeMap(vec2i const & Size, Graphics::ITexture::EMipMaps const MipMaps, Graphics::ITexture::EFormatComponents const Components, Graphics::ITexture::EInternalFormatType const Type) = 0;

		virtual SharedPointer<Graphics::IGraphicsContext> GetWindowContext(CWindow * Window) = 0;

	};

	//! \ingroup ionGraphics
	class CGraphicsAPI : public Singleton<CGraphicsAPI>
	{

	public:

		void Init(IGraphicsImplementation * Implementation);

		void PreWindowCreationSetup();
		void PostWindowCreationSetup();

		SharedPointer<Graphics::IVertexShader> CreateVertexShaderFromFile(string const & FileName);
		SharedPointer<Graphics::IGeometryShader> CreateGeometryShaderFromFile(string const & FileName);
		SharedPointer<Graphics::IPixelShader> CreatePixelShaderFromFile(string const & FileName);

		SharedPointer<Graphics::IVertexShader> CreateVertexShaderFromSource(string const & Source);
		SharedPointer<Graphics::IGeometryShader> CreateGeometryShaderFromSource(string const & Source);
		SharedPointer<Graphics::IPixelShader> CreatePixelShaderFromSource(string const & Source);

		SharedPointer<Graphics::IShaderProgram> CreateShaderProgram();

		SharedPointer<Graphics::IVertexBuffer> CreateVertexBuffer();
		SharedPointer<Graphics::IIndexBuffer> CreateIndexBuffer();

		SharedPointer<Graphics::IDepthBuffer> CreateDepthBuffer(vec2i const & Size);

		Graphics::IDrawContext * CreateDrawContext();

		SharedPointer<Graphics::ITexture2D> CreateTexture2D(vec2i const & Size, Graphics::ITexture::EMipMaps const MipMaps, Graphics::ITexture::EFormatComponents const Components, Graphics::ITexture::EInternalFormatType const Type);
		SharedPointer<Graphics::ITexture2D> CreateTexture2D(CImage * Image, Graphics::ITexture::EMipMaps const MipMaps = Graphics::ITexture::EMipMaps::True);
		SharedPointer<Graphics::ITexture3D> CreateTexture3D(vec3i const & Size, Graphics::ITexture::EMipMaps const MipMaps, Graphics::ITexture::EFormatComponents const Components, Graphics::ITexture::EInternalFormatType const Type);
		SharedPointer<Graphics::ITexture2DArray> CreateTexture2DArray(vec3i const & Size, Graphics::ITexture::EMipMaps const MipMaps, Graphics::ITexture::EFormatComponents const Components, Graphics::ITexture::EInternalFormatType const Type);
		SharedPointer<Graphics::ITextureCubeMap> CreateTextureCubeMap(vec2i const & Size, Graphics::ITexture::EMipMaps const MipMaps, Graphics::ITexture::EFormatComponents const Components, Graphics::ITexture::EInternalFormatType const Type);
		SharedPointer<Graphics::ITextureCubeMap> CreateTextureCubeMap(vector<CImage *> const & Images, Graphics::ITexture::EMipMaps const MipMaps = Graphics::ITexture::EMipMaps::True);

		SharedPointer<Graphics::IGraphicsContext> GetWindowContext(CWindow * Window);

	protected:

		IGraphicsImplementation * Implementation = nullptr;

	private:

		friend class Singleton<CGraphicsAPI>;
		CGraphicsAPI()
		{}

	};

}
