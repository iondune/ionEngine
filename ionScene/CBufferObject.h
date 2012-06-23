#ifndef _CABBAGE_SCENE_CBUFFEROBJECT_H_INCLUDED_
#define _CABBAGE_SCENE_CBUFFEROBJECT_H_INCLUDED_

#include <vector>

#ifdef __unix__
#include<GL/gl.h>
#include<GL/glu.h>
#endif

#ifdef _WIN32
#include <GL\glew.h>
#endif


template <typename T>
class CBufferObject
{

    GLuint Handle;
    bool IndexBuffer;
    bool Dirty;
    unsigned int AllocatedSize;
    GLenum Usage;

    std::vector<T> Elements;

    void reallocate(unsigned int const size, void * data)
    {
        glDeleteBuffers(1, & Handle);
        allocate(size, data);
    }

    void allocate(unsigned int const size, void * data = 0)
    {
        glGenBuffers(1, & Handle);
        glBindBuffer(IndexBuffer ? GL_ELEMENT_ARRAY_BUFFER : GL_ARRAY_BUFFER, Handle);
        glBufferData(IndexBuffer ? GL_ELEMENT_ARRAY_BUFFER : GL_ARRAY_BUFFER, size * sizeof(T), data, Usage);
        AllocatedSize = size;
    }

public:

    CBufferObject(unsigned int const preAllocate = 0, GLenum const usage = GL_STATIC_DRAW)
        : Handle(0), IndexBuffer(false), Dirty(true), AllocatedSize(0), Usage(usage)
    {
        if (preAllocate)
            allocate(preAllocate);
    }

    ~CBufferObject()
    {
        glDeleteBuffers(1, & Handle);
    }

    std::vector<T> const & getElements() const
    {
        return Elements;
    }

    std::vector<T> & getElements()
    {
        return Elements;
    }

    T const & operator [] (unsigned int const i) const
    {
        return Elements[i];
    }

    T & operator [] (unsigned int const i)
    {
        return Elements[i];
    }

    void push_back(T const element)
    {
        Elements.push_back(element);
    }

    unsigned int const size() const
    {
        return Elements.size();
    }

    bool const isIndexBuffer() const
    {
        return IndexBuffer;
    }

	void clear()
	{
		Elements.clear();
		Dirty = true;
	}

    void setIsIndexBuffer(bool const isIndexBuffer)
    {
        IndexBuffer = isIndexBuffer;
    }

    bool const isDirty() const
    {
        return Dirty;
    }

    void setIsDirty(bool const isDirty)
    {
        Dirty = isDirty;
    }

    unsigned int const getHandle() const
    {
        return Handle;
    }

    virtual void syncData()
    {
		if (! Elements.size())
			return;

        if (! Handle)
        {
            allocate(Elements.size(), & Elements[0]);
        }
        else
        {
            if (Elements.size() <= AllocatedSize)
            {
                glBindBuffer(IndexBuffer ? GL_ELEMENT_ARRAY_BUFFER : GL_ARRAY_BUFFER, Handle);
                glBufferSubData(IndexBuffer ? GL_ELEMENT_ARRAY_BUFFER : GL_ARRAY_BUFFER, 0, Elements.size() * sizeof(T), & Elements[0]);
            }
            else
            {
                reallocate(Elements.size(), & Elements[0]);
            }
        }

        Dirty = false;
    }

};

#endif
