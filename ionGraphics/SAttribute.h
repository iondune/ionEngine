#ifndef _ION_SCENE_SATTRIBUTE_H_INCLUDED_
#define _ION_SCENE_SATTRIBUTE_H_INCLUDED_

#include "CShaderContext.h"
#include "CBufferObject.h"


class IAttribute
{

public:
	
	virtual void Load() const = 0;
	virtual void Bind(GLint const handle) const = 0;
	virtual void Bind(GLint const handle, CShaderContext & shaderContext) const = 0;
	virtual void Unbind(GLuint const handle) const = 0;

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

	void Load() const
	{
		if (Buffer && Buffer->isDirty())
			Buffer->syncData();
	}

	void Bind(GLint const Handle) const
	{
		load();

		if (Buffer)
		{
			glEnableVertexAttribArray(Handle);
			glBindBuffer(GL_ARRAY_BUFFER, Buffer->getHandle());
			glVertexAttribPointer(Handle, ElementSize, GL_FLOAT, GL_FALSE, 0, 0);
		}
	}

	void Bind(GLint const handle, CShaderContext & shaderContext) const
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
static sharedPtr<IAttribute const> BindAttribute(CBufferObject<T> & Attribute, int const ElementSize = 4)
{
	return sharedPtr<IAttribute const>(new SAttribute<T>(& Attribute, ElementSize));
}

#endif
