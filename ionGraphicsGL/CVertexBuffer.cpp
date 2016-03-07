
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
			
			void CVertexBuffer::UploadData(void const * const Data, size_t const DataSize, size_t const NumberOfElements)
			{
				CheckedGLCall(glBindBuffer(GL_ARRAY_BUFFER, Handle));
				CheckedGLCall(glBufferData(GL_ARRAY_BUFFER, NumberOfElements * DataSize, Data, GL_STATIC_DRAW));
				CheckedGLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
			}

			void CVertexBuffer::SetInputLayout(SInputLayoutElement * InputLayoutArray, int const NumElements)
			{
				InputLayout.clear();
				InputLayout.insert(InputLayout.begin(), InputLayoutArray, InputLayoutArray + NumElements);
			}

			void CVertexBuffer::SetInstancingEnabled(bool const Enabled)
			{
				Instancing = Enabled;
			}

		}
	}
}
