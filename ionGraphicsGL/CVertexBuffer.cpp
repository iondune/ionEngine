
#include "CVertexBuffer.h"

#include <glad/glad.h>


namespace ion
{
	namespace Graphics
	{
		namespace GL
		{

			CVertexBuffer::~CVertexBuffer()
			{
				CheckedGLCall(glDeleteBuffers(1, &Handle));
			}
			
			void CVertexBuffer::SetInputLayout(SInputLayoutElement * InputLayoutArray, int const NumElements)
			{
				InputLayout.clear();
				InputLayout.insert(InputLayout.begin(), InputLayoutArray, InputLayoutArray + NumElements);
			}

		}
	}
}
