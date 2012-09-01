#ifndef _CABBAGE_SCENE_CRENDERBUFFEROBJECT_H_INCLUDED_
#define _CABBAGE_SCENE_CRENDERBUFFEROBJECT_H_INCLUDED_

#include <GL/glew.h>
#include <SSize2.h>

#include "IRenderTarget.h"


class CRenderBufferObject : public IRenderTarget
{

	GLuint Handle;

public:

	CRenderBufferObject(GLenum const Format, SSize2 const & Size);
	~CRenderBufferObject();

	GLuint const getHandle();

};

#endif
