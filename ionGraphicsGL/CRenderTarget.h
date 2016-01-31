
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionGraphics.h>


namespace ion
{
	namespace Graphics
	{
		namespace GL
		{
			
			class CRenderTarget : public IRenderTarget
			{

			public:

				void ClearColor();
				void ClearDepth();

				uint Handle;
			
			};

		}
	}
}
