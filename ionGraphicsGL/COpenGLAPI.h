
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

			IVertexShader * CreateVertexShaderFromFile(string const & FileName);
			IPixelShader * CreatePixelShaderFromFile(string const & FileName);
			IVertexShader * CreateVertexShaderFromSource(string const & Source);
			IPixelShader * CreatePixelShaderFromSource(string const & Source);

			IShaderProgram * CreateShaderProgram();

			IVertexBuffer * CreateVertexBuffer(float const * const Data, size_t const Elements);
			IIndexBuffer * CreateIndexBuffer(void const * Data, size_t const Elements, EValueType const ValueType);

			ITexture2D * CreateTexture2D(vec2u const & Size, ITexture::EMipMaps const MipMaps, ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type);
			ITexture3D * CreateTexture3D(vec3u const & Size, ITexture::EMipMaps const MipMaps, ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type);

			IPipelineState * CreatePipelineState();

			IRenderTarget * GetWindowBackBuffer(CWindow * Window);

			void Draw(IPipelineState * State);

		};
	}
}
