
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
			
			class CRenderTarget : public IRenderTarget
			{

			public:

				CRenderTarget(CWindow * Window);

				void ClearColor();
				void ClearDepth();
				void ClearColorAndDepth();

				void SetClearColor(color3f const & Color);

				CWindow * Window = nullptr;
				color3f Color;
				uint Handle = 0;
			
			};

		}
	}
}
