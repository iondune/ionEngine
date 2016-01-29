
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionGraphics.h>

#include "Utilities.h"

#include "Buffer.h"
#include "Program.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "Uniform.h"

#include "Context.h"
#include "DrawContext.h"

#include "Framebuffer.h"
#include "Renderbuffer.h"


namespace ion
{
	namespace Graphics
	{
		class COpenGLAPI : public IGraphicsAPI
		{

		public:

			IVertexShader * CreateVertexShaderFromFile(string const & FileName);
			IPixelShader * CreatePixelShaderFromFile(string const & FileName);
			IVertexShader * CreateVertexShaderFromSource(string const & Source);
			IPixelShader * CreatePixelShaderFromSource(string const & Source);

			IShaderProgram * CreateShaderProgram();

			IVertexBuffer * CreateVertexBuffer(float const * const Data, size_t const Elements);
			IIndexBuffer * CreateIndexBuffer(void const * Data, size_t const Elements, EValueType const ValueType);
			IPipelineState * CreatePipelineState();

			void Draw(IPipelineState * State);

		};
	}
}
