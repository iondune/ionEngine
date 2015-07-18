
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
		}

		void Context::Clear(std::vector<EBuffer> Buffers)
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

		void Context::SetClearColor(color4f const & Color)
		{
			CheckedGLCall(glClearColor(Color.Red, Color.Green, Color.Blue, Color.Alpha));
		}

		byte * Context::ReadPixels()
		{
			int const Width = GetViewportSize().X;
			int const Height = GetViewportSize().Y;
			int const BytesPerPixel = 4;

			byte * buffer = new byte[Width * Height * BytesPerPixel]();

			CheckedGLCall(glReadPixels(0, 0, Width, Height, GL_RGBA, GL_UNSIGNED_BYTE, buffer));
			return buffer;
		}

		vec2i Context::GetViewportSize()
		{
			int viewport[4];
			CheckedGLCall(glGetIntegerv(GL_VIEWPORT, viewport));

			return vec2i(viewport[2] - viewport[0], viewport[3] - viewport[1]);
		}
	}
}
