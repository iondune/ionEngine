
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionWindow.h>

#include "Enums.h"
#include "IShaderProgram.h"
#include "IVertexBuffer.h"
#include "IIndexBuffer.h"
#include "ITexture.h"
#include "IGraphicsContext.h"


namespace ion
{
	namespace Graphics
	{

		class IGraphicsAPI
		{

		public:

			virtual SharedPointer<IVertexShader> CreateVertexShaderFromFile(string const & FileName) = 0;
			virtual SharedPointer<IPixelShader> CreatePixelShaderFromFile(string const & FileName) = 0;
			virtual SharedPointer<IVertexShader> CreateVertexShaderFromSource(string const & Source) = 0;
			virtual SharedPointer<IPixelShader> CreatePixelShaderFromSource(string const & Source) = 0;

			virtual SharedPointer<IShaderProgram> CreateShaderProgram() = 0;

			virtual SharedPointer<IVertexBuffer> CreateVertexBuffer() = 0;
			virtual SharedPointer<IIndexBuffer> CreateIndexBuffer() = 0;

			virtual SharedPointer<ITexture2D> CreateTexture2D(vec2u const & Size, ITexture::EMipMaps const MipMaps, ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type) = 0;
			virtual SharedPointer<ITexture3D> CreateTexture3D(vec3u const & Size, ITexture::EMipMaps const MipMaps, ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type) = 0;

			virtual SharedPointer<IGraphicsContext> GetWindowContext(CWindow * Window) = 0;

		};

	}
}
