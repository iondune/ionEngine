
#include "CVertexBuffer.h"


namespace ion
{
	namespace Graphics
	{
		namespace GL
		{
			
			void CVertexBuffer::SetInputLayout(SInputLayoutElement * InputLayoutArray, int const NumElements)
			{
				InputLayout.clear();
				InputLayout.insert(InputLayout.begin(), InputLayoutArray, InputLayoutArray + NumElements);
			}

		}
	}
}
