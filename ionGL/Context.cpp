
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
	}
}
