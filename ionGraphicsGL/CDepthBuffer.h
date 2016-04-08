
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionGraphics.h>

#include "Utilities.h"


namespace ion
{
	namespace Graphics
	{
		namespace GL
		{

			class CDepthBuffer : public IDepthBuffer
			{
			public:

				CDepthBuffer(vec2i const & Size);
				~CDepthBuffer();

				uint Handle = 0;

			};
		}
	}
}
