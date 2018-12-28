
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

			CImage * CRenderTarget::ReadImage()
			{
				int const Width = Window->GetSize().X;
				int const Height = Window->GetSize().Y;
				int const BytesPerPixel = 4;

				byte * buffer = new byte[Width * Height * BytesPerPixel]();

				Bind();
				CheckedGLCall(glReadPixels(0, 0, Width, Height, GL_RGBA, GL_UNSIGNED_BYTE, buffer));
				CImage * Image = new CImage(buffer, Window->GetSize());
				Image->FlipY();
				return Image;
			}

			void CRenderTarget::Bind()
			{
				if (CurrentlyBound != this)
				{
					CheckedGLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
					if (SpecifiedViewport)
					{
						CheckedGLCall(glViewport(ViewportMin.X, ViewportMin.Y, ViewportMax.X, ViewportMax.Y));
					}
					else
					{
						CheckedGLCall(glViewport(0, 0, Window->GetSize().X, Window->GetSize().Y));
					}
					CurrentlyBound = this;
				}
			}

			IRenderTarget * CRenderTarget::GetCurrentlyBound()
			{
				return CurrentlyBound;
			}

			void CRenderTarget::SetViewport(vec2i const & Min, vec2i const & Max)
			{
				ViewportMin = Min;
				ViewportMax = Max;
				SpecifiedViewport = true;
			}

			void CRenderTarget::ClearViewport()
			{
				SpecifiedViewport = false;
			}

			CRenderTarget * CRenderTarget::CurrentlyBound = nullptr;;

		}
	}
}
