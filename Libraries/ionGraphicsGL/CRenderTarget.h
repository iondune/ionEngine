
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionGraphics.h>
#include <ionWindow.h>


namespace ion
{
	namespace Graphics
	{
		namespace GL
		{
			
			class CRenderTarget : public virtual IRenderTarget
			{

			public:

				CRenderTarget(CWindow * Window);

				void ClearColor();
				void ClearDepth();
				void ClearColorAndDepth();

				void SetClearColor(color4f const & Color);

				virtual CImage * ReadImage();

				virtual void Bind();
				virtual IRenderTarget * GetCurrentlyBound();

				CWindow * Window = nullptr;
				color4f Color;
				vec2i ViewportMin;
				vec2i ViewportMax;
				bool SpecifiedViewport = false;

				virtual void SetViewport(vec2i const & Min, vec2i const & Max);
				virtual void ClearViewport();

				static CRenderTarget * CurrentlyBound;
			
			};

		}
	}
}
