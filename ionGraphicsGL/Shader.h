
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

		class CVertexShader : public IVertexShader
		{

		public:

			int Handle = -1;

		};

		class CPixelShader : public IPixelShader
		{

		public:

			int Handle = -1;

		};
	}
	}
}
