
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

			SharedPtr<IVertexBuffer> CreateVertexBuffer(float const * const Data, size_t const Elements);
			SharedPtr<IVertexBuffer> CreateVertexBuffer();
			SharedPtr<IIndexBuffer> CreateIndexBuffer(void const * Data, size_t const Elements, EValueType const ValueType);
			SharedPtr<IIndexBuffer> CreateIndexBuffer();

			SharedPtr<ITexture2D> CreateTexture2D(vec2u const & Size, ITexture::EMipMaps const MipMaps, ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type);
			SharedPtr<ITexture3D> CreateTexture3D(vec3u const & Size, ITexture::EMipMaps const MipMaps, ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type);

			SharedPtr<IPipelineState> CreatePipelineState();

			SharedPtr<IRenderTarget> GetWindowBackBuffer(CWindow * Window);

			void Draw(SharedPtr<IPipelineState> State);
			void DrawInstanced(SharedPtr<IPipelineState> State, uint const InstanceCount);

		protected:

			void InternalDrawSetup(SharedPtr<IPipelineState> State);
			void InternalDrawTeardown(SharedPtr<IPipelineState> State);
		};
	}
}
