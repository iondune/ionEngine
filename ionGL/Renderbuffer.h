
#pragma once

#include <ionCore.h>
#include <ionMath.h>

#include "Context.h"


namespace ion
{
	namespace GL
	{
		class Renderbuffer
		{
		public:

			Renderbuffer(vec2i const & Size = Context::GetViewportSize());
			~Renderbuffer();

		private:

			friend class Framebuffer;
			u32 Handle;
		};
	}
}
