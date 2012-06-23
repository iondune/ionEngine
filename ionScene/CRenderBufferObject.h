#ifndef _CABBAGE_SCENE_CRENDERBUFFEROBJECT_H_INCLUDED_
#define _CABBAGE_SCENE_CRENDERBUFFEROBJECT_H_INCLUDED_

#ifdef __unix__
#include<GL/gl.h>
#endif

#ifdef _WIN32
#include <GL/glew.h>
#endif

#include <SSize2.h>


class CRenderBufferObject
{

	GLuint Handle;

public:

	CRenderBufferObject(GLenum const Format, SSize2 const & Size);
	~CRenderBufferObject();

	GLuint const getHandle();

};

#endif
