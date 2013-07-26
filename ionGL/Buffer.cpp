#include "ionGL.h"
#include "Utilities.h"


////////////
// Buffer //
////////////

void GL::Buffer::Data(u32 const size, void const * const data,
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

void GL::Buffer::SubData(u32 const size, u32 const offset, void const * const data)
{
	Bind();
	CheckedGLCall(glBufferSubData(GetTarget(), offset, size, data));
	Unbind();
}

void GL::Buffer::Delete()
{
	delete this;
}

GL::Buffer::~Buffer()
{
	glDeleteBuffers(1, & Handle);
}

GL::Buffer::Buffer()
{
	glGenBuffers(1, & Handle);
}


//////////////////////
// Attribute Buffer //
//////////////////////

void GL::AttributeBuffer::Bind()
{
	CheckedGLCall(glBindBuffer(GL_ARRAY_BUFFER, Handle));
}

void GL::AttributeBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

u32 GL::AttributeBuffer::GetTarget()
{
	return GL_ARRAY_BUFFER;
}


//////////////////
// Index Buffer //
//////////////////

void GL::IndexBuffer::Bind()
{
	CheckedGLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Handle));
}

void GL::IndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

u32 GL::IndexBuffer::GetTarget()
{
	return GL_ELEMENT_ARRAY_BUFFER;
}
