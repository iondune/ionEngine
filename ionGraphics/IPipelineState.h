
#pragma once

#include <ionCore.h>

#include "Shaders.h"
#include "Buffers.h"
#include "Uniforms.h"
#include "Textures.h"


namespace ion
{
	namespace Graphics
	{

		class IPipelineState
		{

		public:

			virtual void SetProgram(IShaderProgram * ShaderProgram) = 0;
			virtual void SetVertexBuffer(IVertexBuffer * VertexBuffer) = 0;
			virtual void SetIndexBuffer(IIndexBuffer * IndexBuffer) = 0;
			virtual void SetUniform(string const & Name, IUniform * Uniform) = 0;
			virtual void SetTexture(string const & Name, ITexture * Texture) = 0;

			virtual void OfferUniform(string const & Name, IUniform * Uniform) = 0;

			virtual uint GetUnboundUniformCount() const = 0;
			virtual string GetUnboundUniform(uint const Index) const = 0;

			virtual void Load() = 0;

		};

	}
}
