
#include "VertexArray.h"
#include <GL/glew.h>


namespace ion
{
	namespace GL
	{
		VertexArray::VertexArray()
		{
			BoundIndexBuffer = 0;
			PrimativeType = EPrimativeType::Triangles;

			glGenVertexArrays(1, & Handle);
		}

		void VertexArray::SetIndexBuffer(IndexBuffer * ibo)
		{
			glBindVertexArray(Handle);
			BoundIndexBuffer = ibo;
			BoundIndexBuffer->Bind();
			glBindVertexArray(0);
		}

		void VertexArray::BindAttribute(u32 const index, VertexBuffer * vbo)
		{
			glBindVertexArray(Handle);
			glEnableVertexAttribArray(index);
			vbo->Bind();
			glVertexAttribPointer(index, vbo->Components(), Util::TypeMatrix[(int) vbo->Type()], GL_FALSE, 0, 0);
			vbo->Unbind();
			glBindVertexArray(0);
		}

		void VertexArray::Draw()
		{
			glBindVertexArray(Handle);
			if (BoundIndexBuffer)
			{
				glDrawElements(
					Util::PrimativeMatrix[(int) PrimativeType],
					BoundIndexBuffer->Size(),
					Util::TypeMatrix[(int) BoundIndexBuffer->Type()], 0);
			}
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
