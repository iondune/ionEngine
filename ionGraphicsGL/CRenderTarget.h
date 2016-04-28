
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

				virtual void Bind();

				CWindow * Window = nullptr;
				color4f Color;

				static CRenderTarget * CurrentlyBound;
			
			};

		}
	}
}
