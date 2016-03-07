
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

			virtual SharedPtr<IVertexShader> CreateVertexShaderFromFile(string const & FileName) = 0;
			virtual SharedPtr<IPixelShader> CreatePixelShaderFromFile(string const & FileName) = 0;
			virtual SharedPtr<IVertexShader> CreateVertexShaderFromSource(string const & Source) = 0;
			virtual SharedPtr<IPixelShader> CreatePixelShaderFromSource(string const & Source) = 0;

			virtual SharedPtr<IShaderProgram> CreateShaderProgram() = 0;

			virtual SharedPtr<IVertexBuffer> CreateVertexBuffer() = 0;
			virtual SharedPtr<IIndexBuffer> CreateIndexBuffer() = 0;

			virtual SharedPtr<ITexture2D> CreateTexture2D(vec2u const & Size, ITexture::EMipMaps const MipMaps, ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type) = 0;
			virtual SharedPtr<ITexture3D> CreateTexture3D(vec3u const & Size, ITexture::EMipMaps const MipMaps, ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type) = 0;

			virtual SharedPtr<IGraphicsContext> GetWindowContext(CWindow * Window) = 0;

		};

	}
}
