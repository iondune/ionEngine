
#pragma once

#include <ionCore.h>

#include "IVertexBuffer.h"


namespace ion
{
	namespace Graphics
	{

		//! \ingroup ionGraphics
		class IInputLayout
		{

		public:

			virtual ~IInputLayout() = default;

		};

		//! \ingroup ionGraphics
		struct SInputBufferLayout
		{
			int Slot = -1;
			bool Instanced = false;
			vector<SInputLayoutElement> LayoutElements;

			SInputBufferLayout(int const slot, vector<SInputLayoutElement> const & layoutElements, bool const instanced = false)
				: Slot(slot), LayoutElements(layoutElements), Instanced(instanced)
			{}
		};

	}
}
