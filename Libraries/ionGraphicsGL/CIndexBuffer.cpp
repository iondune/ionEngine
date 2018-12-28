
#include "CIndexBuffer.h"

#include <glad/glad.h>


namespace ion
{
	namespace Graphics
	{
		namespace GL
		{

			CIndexBuffer::~CIndexBuffer()
			{
				CheckedGLCall(glDeleteBuffers(1, &Handle));
			}

			void CIndexBuffer::UploadData(void const * Data, size_t const Elements, EValueType const ValueType)
			{
				CheckedGLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Handle));
				CheckedGLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, Elements * GetValueTypeSize(ValueType), Data, GL_STATIC_DRAW));
				CheckedGLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
				Size = Elements;
			}

		}
	}
}
