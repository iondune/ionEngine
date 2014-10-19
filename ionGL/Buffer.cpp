
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

		template <>
		void Buffer::Data<f32>(u64 const size, f32 const * const data, u32 const components,
			EAccessFrequency const accessFrequency, EAccessNature const accessNature)
		{
			DataType = EFormatType::F32;
			InternalData(size, data, components, accessFrequency, accessNature);
		}

		template <>
		void Buffer::Data<u32>(u64 const size, u32 const * const data, u32 const components,
			EAccessFrequency const accessFrequency, EAccessNature const accessNature)
		{
			DataType = EFormatType::U32;
			InternalData(size, data, components, accessFrequency, accessNature);
		}

		void Buffer::SubData(u64 const size, u64 const offset, void const * const data)
		{
			Bind();
			CheckedGLCall(glBufferSubData(GetTarget(), Min(offset, DataSize), Min(size, DataSize - offset), data));
			Unbind();
		}

		u64 Buffer::Size() const
		{
			return DataSize;
		}

		u32 Buffer::Components() const
		{
			return DataComponents;
		}

		u64 Buffer::Elements() const
		{
			return DataSize / Util::SizeMatrix[(int) DataType];
		}

		EFormatType Buffer::Type() const
		{
			return DataType;
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
			DataSize = -1;
			DataComponents = -1;
			DataType = EFormatType::U8;
		}

		void Buffer::Bind()
		{
			CheckedGLCall(glBindBuffer(GetTarget(), Handle));
		}

		void Buffer::Unbind()
		{
			CheckedGLCall(glBindBuffer(GetTarget(), 0));
		}

		void Buffer::InternalData(size_t const size, void const * const data, u32 const components,
			EAccessFrequency const accessFrequency, EAccessNature const accessNature)
		{
			static u32 const UsageMatrix[3][3] =
			{
				{ GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY },
				{ GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY },
				{ GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, GL_DYNAMIC_COPY }
			};

			Bind();
			CheckedGLCall(glBufferData(GetTarget(), size, data, UsageMatrix[(int) accessFrequency][(int) accessNature]));
			DataSize = size;
			DataComponents = components;
			Unbind();
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
