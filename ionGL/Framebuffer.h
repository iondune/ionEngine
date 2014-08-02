
#pragma once

#include <ionCore.h>
#include <ionMath.h>


namespace ion
{
	namespace GL
	{
		class Framebuffer
		{
		public:

			Framebuffer();
			~Framebuffer();

		private:

			u32 Handle;
		};
	}
}
