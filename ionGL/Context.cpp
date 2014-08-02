
#include "Context.h"
#include <GL/glew.h>

#include "Utilities.h"


namespace ion
{
	namespace GL
	{
		void Context::Init()
		{
			CheckedGLCall(glEnable(GL_DEPTH_TEST));
			CheckedGLCall(glDepthFunc(GL_LEQUAL));

			CheckedGLCall(glEnable(GL_TEXTURE_2D));
		}

		void Context::Clear(std::initializer_list<EBuffer> Buffers)
		{
			static u32 const BufferLookup[3] =
			{
				GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT
			};
			int BitMask = 0;
			for (auto Buffer : Buffers)
				BitMask |= BufferLookup[(int) Buffer];
			CheckedGLCall(glClear(BitMask));
		}

		vec2i Context::GetViewportSize()
		{
			int viewport[4];
			CheckedGLCall(glGetIntegerv(GL_VIEWPORT, viewport));

			return vec2i(viewport[2] - viewport[0], viewport[3] - viewport[1]);
		}
	}
}
