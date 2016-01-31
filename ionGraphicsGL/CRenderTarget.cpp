
#include "CRenderTarget.h"

#include "Utilities.h"

#include <GL/glew.h>


namespace ion
{
	namespace Graphics
	{
		namespace GL
		{

			void CRenderTarget::ClearColor()
			{
				CheckedGLCall(glClear(GL_COLOR_BUFFER_BIT));
			}

			void CRenderTarget::ClearDepth()
			{
				CheckedGLCall(glClear(GL_DEPTH_BUFFER_BIT));
			}

		}
	}
}
