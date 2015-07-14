
#include "VertexArray.h"
#include <GL/glew.h>

#include "Utilities.h"


namespace ion
{
	namespace GL
	{
		VertexArray::VertexArray(EPrimitiveType const PrimitiveType)
		{
			this->PrimitiveType = PrimitiveType;

			CheckedGLCall(glGenVertexArrays(1, & Handle));
		}

		void VertexArray::SetIndexBuffer(IndexBuffer * ibo)
		{
			if (! ibo)
				return;

			CheckedGLCall(glBindVertexArray(Handle));
			BoundIndexBuffer = ibo;
			BoundIndexBuffer->Bind();
			CheckedGLCall(glBindVertexArray(0));
		}

		void VertexArray::SetElementCount(uint count)
		{
			this->ElementCount = count;
		}

		void VertexArray::BindAttribute(u32 const index, VertexBuffer * vbo)
		{
			CheckedGLCall(glBindVertexArray(Handle));
			CheckedGLCall(glEnableVertexAttribArray(index));
			vbo->Bind();
			CheckedGLCall(glVertexAttribPointer(index, vbo->Components(), Util::TypeMatrix[(int) vbo->Type()], GL_FALSE, 0, 0));
			vbo->Unbind();
			CheckedGLCall(glBindVertexArray(0));
		}

		void VertexArray::Draw()
		{
			if (BoundIndexBuffer)
			{
				if (BoundIndexBuffer->Elements() > INT_MAX)
					cerr << "Index buffer is too large for OpenGL rendering: " << BoundIndexBuffer << " (" << BoundIndexBuffer->Elements() << ")" << endl;
				CheckedGLCall(glBindVertexArray(Handle));
				glDrawElements(
					Util::PrimitiveMatrix[(int) PrimitiveType],
					(int) BoundIndexBuffer->Elements(),
					Util::TypeMatrix[(int) BoundIndexBuffer->Type()], 0);
				CheckedGLCall(glBindVertexArray(0));
			}
			else
			{
				CheckedGLCall(glBindVertexArray(Handle));
				glDrawArrays(
					Util::PrimitiveMatrix[(int) PrimitiveType],
					0,
					ElementCount * Util::PrimitiveVertices[(int) PrimitiveType]);
				CheckedGLCall(glBindVertexArray(0));
			}

		}

		void VertexArray::Delete()
		{
			delete this;
		}

		VertexArray::~VertexArray()
		{
			CheckedGLCall(glDeleteVertexArrays(1, & Handle));
		}
	}
}
