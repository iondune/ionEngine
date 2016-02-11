
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

			class CVertexBuffer : public IVertexBuffer
			{

			public:

				void SetInputLayout(SInputLayoutElement * InputLayout, int const NumElements);


				uint Handle = 0;
				vector<SInputLayoutElement> InputLayout;

			};

		}
	}
}
