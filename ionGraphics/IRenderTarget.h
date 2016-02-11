
#pragma once

#include <ionCore.h>
#include <ionMath.h>


namespace ion
{
	namespace Graphics
	{

		class IRenderTarget
		{

		public:

			virtual void ClearColor() = 0;
			virtual void ClearDepth() = 0;
			virtual void ClearColorAndDepth() = 0;

			virtual void SetClearColor(color3f const & Color) = 0;

		};

	}
}
