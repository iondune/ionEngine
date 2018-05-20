
#pragma once

#include <ionCore.h>
#include <ionMath.h>

#include "Enums.h"
#include "IShaderProgram.h"
#include "IVertexBuffer.h"
#include "IIndexBuffer.h"
#include "ITexture.h"
#include "IGraphicsContext.h"
#include "IGraphicsImplementation.h"
#include "IDrawContext.h"


namespace ion
{

	//! \ingroup ionGraphics
	class CGraphicsAPI : public Singleton<CGraphicsAPI>
	{

	public:

		void Init(IGraphicsImplementation * Implementation);

		void PreWindowCreationSetup();
		void PostWindowCreationSetup(CWindow * Window);
		bool OnWindowSwap(CWindow * Window);

		SharedPointer<Graphics::IVertexStage> CreateVertexStageFromFile(string const & FileName);
		SharedPointer<Graphics::IGeometryStage> CreateGeometryStageFromFile(string const & FileName);
		SharedPointer<Graphics::IPixelStage> CreatePixelStageFromFile(string const & FileName);

		SharedPointer<Graphics::IVertexStage> CreateVertexStageFromSource(string const & Source);
		SharedPointer<Graphics::IGeometryStage> CreateGeometryStageFromSource(string const & Source);
		SharedPointer<Graphics::IPixelStage> CreatePixelStageFromSource(string const & Source);

		SharedPointer<Graphics::IShader> CreateShaderProgram();

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
