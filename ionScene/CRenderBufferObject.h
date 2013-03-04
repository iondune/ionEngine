#ifndef _ION_SCENE_CRENDERBUFFEROBJECT_H_INCLUDED_
#define _ION_SCENE_CRENDERBUFFEROBJECT_H_INCLUDED_

#include <GL/glew.h>
#include <ionMath.h>

#include "IRenderTarget.h"


class CRenderBufferObject : public IRenderTarget
{

	GLuint Handle;

public:

	CRenderBufferObject(GLenum const Format, vec2u const & Size);
	~CRenderBufferObject();

	GLuint const getHandle();

	virtual ERenderTargetType const getRenderTargetType();

};

#endif
