
#include "Buffer.h"
#include "Utilities.h"
#include <GL/glew.h>


namespace ion
{
	namespace GL
	{
		//////////
		// Data //
		//////////

		void Buffer::Data(u32 const size, void const * const data,
			EAccessFrequency const accessFrequency,
			EAccessNature const accessNature)
		{
			static u32 const UsageMatrix[3][3] = 
			{
				{GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY},
				{GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY},
				{GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, GL_DYNAMIC_COPY}
			};

			Bind();
			CheckedGLCall(glBufferData(GetTarget(), size, data, UsageMatrix[(int) accessFrequency][(int) accessNature]));
			Unbind();
		}

		void Buffer::SubData(u32 const size, u32 const offset, void const * const data)
		{
			Bind();
			CheckedGLCall(glBufferSubData(GetTarget(), offset, size, data));
			Unbind();
		}


		////////////
		// Buffer //
		////////////

		void Buffer::Delete()
		{
			delete this;
		}

		Buffer::~Buffer()
		{
			glDeleteBuffers(1, & Handle);
		}

		Buffer::Buffer()
		{
			glGenBuffers(1, & Handle);
		}

		void Buffer::Bind()
		{
			CheckedGLCall(glBindBuffer(GetTarget(), Handle));
		}

		void Buffer::Unbind()
		{
			CheckedGLCall(glBindBuffer(GetTarget(), 0));
		}


		//////////////
		// Variants //
		//////////////

		u32 VertexBuffer::GetTarget()
		{
			return GL_ARRAY_BUFFER;
		}

		u32 IndexBuffer::GetTarget()
		{
			return GL_ELEMENT_ARRAY_BUFFER;
		}
	}
}
