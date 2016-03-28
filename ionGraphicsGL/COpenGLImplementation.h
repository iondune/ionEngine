
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

			void PreWindowCreationSetup();
			void PostWindowCreationSetup();

			SharedPointer<IVertexShader> CreateVertexShaderFromSource(string const & Source);
			SharedPointer<IPixelShader> CreatePixelShaderFromSource(string const & Source);

			SharedPointer<IShaderProgram> CreateShaderProgram();

			SharedPointer<IVertexBuffer> CreateVertexBuffer();
			SharedPointer<IIndexBuffer> CreateIndexBuffer();

			SharedPointer<ITexture2D> CreateTexture2D(vec2u const & Size, ITexture::EMipMaps const MipMaps, ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type);
			SharedPointer<ITexture3D> CreateTexture3D(vec3u const & Size, ITexture::EMipMaps const MipMaps, ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type);

			SharedPointer<IGraphicsContext> GetWindowContext(CWindow * Window);

		};
	}
}
