
#pragma once

#include <ionCore.h>
#include <ionMath.h>

#include "VertexArray.h"
#include "Program.h"
#include "Uniform.h"
#include "Texture.h"
#include "Framebuffer.h"
#include "DrawConfig.h"


namespace ion
{
	namespace GL
	{
		class DrawContext
		{
		public:

			// Specify framebuffer here?
			// DrawContext for framebuffer
			// Set Program call
			// then draw

			DrawContext(Framebuffer * Framebuffer = DefaultFrameBuffer);
			~DrawContext();
			
			void LoadProgram(Program * Program);
			void Draw(DrawConfig * DrawConfig);

			void BindUniform(string const & Name, Uniform const * Value);

		protected:

			Framebuffer * Target = nullptr;
			Program * BoundProgram = nullptr;
			VertexArray * BoundArray = nullptr;
		};
	}
}
