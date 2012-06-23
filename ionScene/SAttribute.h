#ifndef _CABBAGE_SCENE_SATTRIBUTE_H_INCLUDED_
#define _CABBAGE_SCENE_SATTRIBUTE_H_INCLUDED_

#include <boost/shared_ptr.hpp>
#include "CShaderContext.h"
#include "CBufferObject.h"


class IAttribute
{

public:
	
	virtual void load() const = 0;
	virtual void bind(GLint const handle) const = 0;
	virtual void bind(GLint const handle, CShaderContext & shaderContext) const = 0;
	virtual void unbind(GLuint const handle) const = 0;

};

template <typename T>
class SAttribute : public IAttribute
{

public:

	CBufferObject<T> * Buffer;
	int ElementSize;

	SAttribute()
		: Buffer(0), ElementSize(0)
	{}

	SAttribute(CBufferObject<T> * buffer, int const elementSize = 4)
		: Buffer(buffer), ElementSize(elementSize)
	{}

	void load() const
	{
		if (Buffer && Buffer->isDirty())
			Buffer->syncData();
	}

	void bind(GLint const Handle) const
	{
		load();

		if (Buffer)
		{
			glEnableVertexAttribArray(Handle);
			glBindBuffer(GL_ARRAY_BUFFER, Buffer->getHandle());
			glVertexAttribPointer(Handle, ElementSize, GL_FLOAT, GL_FALSE, 0, 0);
		}
	}

	void bind(GLint const handle, CShaderContext & shaderContext) const
	{
		load();
		if (Buffer)
			shaderContext.bindBufferObject(handle, Buffer->getHandle(), ElementSize);
	}

	void unbind(GLuint const handle) const
	{
        glDisableVertexAttribArray(handle);
	}

};

template <typename T>
static boost::shared_ptr<IAttribute const> BindAttribute(T const & attribute)
{
	return new boost::shared_ptr<IAttribute const>(new SAttribute<T>(attribute));
}

#endif
