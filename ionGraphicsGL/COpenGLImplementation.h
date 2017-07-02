
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionGraphics.h>


namespace ion
{
	namespace Graphics
	{

		class COpenGLImplementation : public IGraphicsImplementation
		{

		public:

			COpenGLImplementation();

			void UseReverseDepth(bool const ReverseDepth = true);
			bool IsReverseDepth();

			void PreWindowCreationSetup();
			void PostWindowCreationSetup();

			SharedPointer<IVertexShader> CreateVertexShaderFromSource(string const & Source);
			SharedPointer<IGeometryShader> CreateGeometryShaderFromSource(string const & Source);
			SharedPointer<IPixelShader> CreatePixelShaderFromSource(string const & Source);

			SharedPointer<IShaderProgram> CreateShaderProgram();

			SharedPointer<IVertexBuffer> CreateVertexBuffer();
			SharedPointer<IIndexBuffer> CreateIndexBuffer();

			SharedPointer<Graphics::IDepthBuffer> CreateDepthBuffer(vec2i const & Size);

			Graphics::IDrawContext * CreateDrawContext();

			SharedPointer<ITexture2D> CreateTexture2D(vec2i const & Size, ITexture::EMipMaps const MipMaps, ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type);
			SharedPointer<ITexture3D> CreateTexture3D(vec3i const & Size, ITexture::EMipMaps const MipMaps, ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type);
			SharedPointer<ITexture2DArray> CreateTexture2DArray(vec3i const & Size, ITexture::EMipMaps const MipMaps, ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type);
			SharedPointer<ITextureCubeMap> CreateTextureCubeMap(vec2i const & Size, ITexture::EMipMaps const MipMaps, ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type);

			SharedPointer<IGraphicsContext> GetWindowContext(CWindow * Window);

		protected:

			bool ReverseDepth = false;

		};
	}
}
