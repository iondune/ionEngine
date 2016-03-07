
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionGraphics.h>


namespace ion
{
	namespace Graphics
	{

		class COpenGLAPI : public IGraphicsAPI
		{

		public:

			COpenGLAPI();

			SharedPtr<IVertexShader> CreateVertexShaderFromFile(string const & FileName);
			SharedPtr<IPixelShader> CreatePixelShaderFromFile(string const & FileName);
			SharedPtr<IVertexShader> CreateVertexShaderFromSource(string const & Source);
			SharedPtr<IPixelShader> CreatePixelShaderFromSource(string const & Source);

			SharedPtr<IShaderProgram> CreateShaderProgram();

			SharedPtr<IVertexBuffer> CreateVertexBuffer();
			SharedPtr<IIndexBuffer> CreateIndexBuffer();

			SharedPtr<ITexture2D> CreateTexture2D(vec2u const & Size, ITexture::EMipMaps const MipMaps, ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type);
			SharedPtr<ITexture3D> CreateTexture3D(vec3u const & Size, ITexture::EMipMaps const MipMaps, ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type);

			SharedPtr<IGraphicsContext> GetWindowContext(CWindow * Window);
		};
	}
}
