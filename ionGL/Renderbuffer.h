
#pragma once

#include <ionCore.h>
#include <ionMath.h>


namespace ion
{
	namespace GL
	{
		class Renderbuffer
		{
		public:

			Renderbuffer();
			~Renderbuffer();

		private:

			friend class Framebuffer;
			u32 Handle;
		};
	}
}
