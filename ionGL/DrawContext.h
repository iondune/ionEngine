
#pragma once

#include <ionCore.h>
#include <ionMath.h>

#include "VertexArray.h"
#include "Program.h"
#include "Uniform.h"


namespace ion
{
	namespace GL
	{
		class DrawContext
		{
		public:

			DrawContext(Program * program);
			~DrawContext();

			void BindUniform(string const & Name, Uniform const * Value);
			void SetVertexArray(VertexArray * Array);
			void Draw();

		protected:

			Program * BoundProgram;
			VertexArray * BoundArray;
		};
	}
}
