
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionGraphics.h>


namespace ion
{
	namespace Graphics
	{
		namespace D3D11
		{

			class CDepthBuffer : public IDepthBuffer
			{
			public:

				CDepthBuffer(vec2i const & Size);
				~CDepthBuffer();

			};

		}
	}
}
