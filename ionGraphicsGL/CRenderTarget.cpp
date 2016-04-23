
#include "CRenderTarget.h"

#include "Utilities.h"

#include <glad/glad.h>


namespace ion
{
	namespace Graphics
	{
		namespace GL
		{

			CRenderTarget::CRenderTarget(CWindow * Window)
			{
				this->Window = Window;
			}

			void CRenderTarget::ClearColor()
			{
				Window->MakeContextCurrent();
				Bind();
				CheckedGLCall(glClearColor(Color.Red, Color.Green, Color.Blue, Color.Alpha));
				CheckedGLCall(glClear(GL_COLOR_BUFFER_BIT));
			}

			void CRenderTarget::ClearDepth()
			{
				Window->MakeContextCurrent();
				Bind();
				CheckedGLCall(glClear(GL_DEPTH_BUFFER_BIT));
			}

			void CRenderTarget::ClearColorAndDepth()
			{
				Window->MakeContextCurrent();
				Bind();
				CheckedGLCall(glClearColor(Color.Red, Color.Green, Color.Blue, Color.Alpha));
				CheckedGLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
			}

			void CRenderTarget::SetClearColor(color4f const & Color)
			{
				this->Color = Color;
			}

			void CRenderTarget::Bind()
			{
				if (CurrentlyBound != this)
				{
					CheckedGLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
					CheckedGLCall(glViewport(0, 0, Window->GetSize().X, Window->GetSize().Y));
					CurrentlyBound = this;
				}
			}

			CRenderTarget * CRenderTarget::CurrentlyBound = nullptr;;

		}
	}
}
