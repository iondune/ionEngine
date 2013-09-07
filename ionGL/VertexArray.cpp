
#include "VertexArray.h"
#include <GL/glew.h>


namespace ion
{
	namespace GL
	{
		VertexArray::VertexArray()
		{
			glGenVertexArrays(1, & Handle);
		}

		void VertexArray::AttributePointer(VertexBuffer * Buffer, u32 const index, u32 const size, EFormatType const type, u32 const stride, void * offset)
		{
			glBindVertexArray(Handle);
			Buffer->Bind();
			glVertexAttribPointer(index, size, Util::TypeMatrix[(int) type], false, stride, offset);
			Buffer->Unbind();
			glBindVertexArray(0);
		}

		void VertexArray::EnableAttribute(u32 const index)
		{
			glBindVertexArray(Handle);
			glEnableVertexAttribArray(index);
			glBindVertexArray(0);
		}

		void VertexArray::DisableAttribute(u32 const index)
		{
			glBindVertexArray(Handle);
			glDisableVertexAttribArray(index);
			glBindVertexArray(0);
		}

		void VertexArray::Delete()
		{
			delete this;
		}

		VertexArray::~VertexArray()
		{
			glDeleteVertexArrays(1, & Handle);
		}
	}
}
