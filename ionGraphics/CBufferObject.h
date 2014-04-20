
#pragma once

#include <GL/glew.h>
#include <ionGL.h>


template <typename T>
class CBufferObject
{

	GLuint Handle;
	bool IndexBuffer;
	bool Dirty;
	uint AllocatedSize;
	GLenum Usage;

	std::vector<T> Elements;

	void Reallocate(uint const size, void * data)
	{
		CheckedGLCall(glDeleteBuffers(1, & Handle));
		Allocate(size, data);
	}

	void Allocate(uint const size, void * data = 0)
	{
		CheckedGLCall(glGenBuffers(1, & Handle));
		CheckedGLCall(glBindBuffer(IndexBuffer ? GL_ELEMENT_ARRAY_BUFFER : GL_ARRAY_BUFFER, Handle));
		CheckedGLCall(glBufferData(IndexBuffer ? GL_ELEMENT_ARRAY_BUFFER : GL_ARRAY_BUFFER, size * sizeof(T), data, Usage));
		AllocatedSize = size;
	}

public:

	CBufferObject(uint const preAllocate = 0, GLenum const usage = GL_STATIC_DRAW)
		: Handle(0), IndexBuffer(false), Dirty(true), AllocatedSize(0), Usage(usage)
	{
		if (preAllocate)
			Allocate(preAllocate);
	}

	~CBufferObject()
	{
		if (Handle)
			CheckedGLCall(glDeleteBuffers(1, & Handle));
	}

	std::vector<T> const & GetElements() const
	{
		return Elements;
	}

	std::vector<T> & GetElements()
	{
		return Elements;
	}

	T const & operator [] (uint const i) const
	{
		return Elements[i];
	}

	T & operator [] (uint const i)
	{
		return Elements[i];
	}

	void Push(T const element)
	{
		Elements.push_back(element);
	}

	uint Size() const
	{
		return Elements.size();
	}

	bool const IsIndexBuffer() const
	{
		return IndexBuffer;
	}

	void Clear()
	{
		Elements.clear();
		Dirty = true;
	}

	void Resize(u32 const size)
	{
		Elements.resize(size);
		Dirty = true;
	}

	void SetIsIndexBuffer(bool const isIndexBuffer)
	{
		IndexBuffer = isIndexBuffer;
	}

	bool const IsDirty() const
	{
		return Dirty;
	}

	void SetIsDirty(bool const isDirty)
	{
		Dirty = isDirty;
	}

	uint const GetHandle() const
	{
		return Handle;
	}

	virtual void SyncData()
	{
		if (! Elements.size())
			return;

		if (! Handle)
		{
			Allocate(Elements.size(), & Elements[0]);
		}
		else
		{
			if (Elements.size() <= AllocatedSize)
			{
				CheckedGLCall(glBindBuffer(IndexBuffer ? GL_ELEMENT_ARRAY_BUFFER : GL_ARRAY_BUFFER, Handle));
				CheckedGLCall(glBufferSubData(IndexBuffer ? GL_ELEMENT_ARRAY_BUFFER : GL_ARRAY_BUFFER, 0, Elements.size() * sizeof(T), & Elements[0]));
				CheckedGLCall(glBindBuffer(IndexBuffer ? GL_ELEMENT_ARRAY_BUFFER : GL_ARRAY_BUFFER, 0));
			}
			else
			{
				Reallocate(Elements.size(), & Elements[0]);
			}
		}

		Dirty = false;
	}

};
