
#pragma once

#if 0

#include <ionCore.h>
#include <ionMath.h>
#include <ionGraphics.h>

#include "VertexArray.h"
#include "Program.h"
#include "Uniform.h"
#include "Texture.h"
#include "Framebuffer.h"
#include "DrawConfig.h"


namespace ion
{
	namespace Graphics
	{
		namespace GL
		{

		class DrawContext
		{
		public:

			DrawContext(Framebuffer * Framebuffer = DefaultFrameBuffer);
			~DrawContext();

			void LoadProgram(IShaderProgram * Program);
			bool Draw(DrawConfig * DrawConfig);

			//! Deprecated.
			void BindUniform(string const & Name, Uniform const * Value);

		protected:

			Framebuffer * Target = nullptr;
			IShaderProgram * BoundProgram = nullptr;
			VertexArray * BoundArray = nullptr;
		};
		}
	}
}

#endif
