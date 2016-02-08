
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionWindow.h>

#include "Enums.h"
#include "Shaders.h"
#include "Buffers.h"
#include "Textures.h"
#include "IPipelineState.h"
#include "IRenderTarget.h"


namespace ion
{
	namespace Graphics
	{

		class IGraphicsAPI
		{

		public:

			virtual IVertexShader * CreateVertexShaderFromFile(string const & FileName) = 0;
			virtual IPixelShader * CreatePixelShaderFromFile(string const & FileName) = 0;
			virtual IVertexShader * CreateVertexShaderFromSource(string const & Source) = 0;
			virtual IPixelShader * CreatePixelShaderFromSource(string const & Source) = 0;

			virtual IShaderProgram * CreateShaderProgram() = 0;

			virtual IVertexBuffer * CreateVertexBuffer(float const * const Data, size_t const Elements) = 0;
			virtual IIndexBuffer * CreateIndexBuffer(void const * Data, size_t const Elements, EValueType const ValueType) = 0;

			virtual ITexture2D * CreateTexture2D(vec2u const & Size, ITexture::EMipMaps const MipMaps, ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type) = 0;
			virtual ITexture3D * CreateTexture3D(vec3u const & Size, ITexture::EMipMaps const MipMaps, ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type) = 0;

			virtual IPipelineState * CreatePipelineState() = 0;

			virtual IRenderTarget * GetWindowBackBuffer(CWindow * Window) = 0;

			virtual void Draw(IPipelineState * State) = 0;

		};

	}
}
