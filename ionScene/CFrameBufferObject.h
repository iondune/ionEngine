#ifndef _CABBAGE_SCENE_CFRAMEBUFFEROBJECT_H_INCLUDED_
#define _CABBAGE_SCENE_CFRAMEBUFFEROBJECT_H_INCLUDED_

#ifdef __unix__
#include<GL/gl.h>
#endif

#ifdef _WIN32
#include <GL/glew.h>
#endif

#include "CRenderBufferObject.h"
#include "CTexture.h"


class CFrameBufferObject
{

	GLuint Handle;

public:

	CFrameBufferObject();
	~CFrameBufferObject();

	void attach(CRenderBufferObject * RenderBufferObject, GLenum const Attachment);
	void attach(CTexture * Texture, GLenum const Attachment);

	GLuint const getHandle();

	void bind();
	void unbind();

	bool const isValid() const;

};

void bindDeviceBackBuffer();

#endif
