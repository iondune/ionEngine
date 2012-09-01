#ifndef _CABBAGE_SCENE_CFRAMEBUFFEROBJECT_H_INCLUDED_
#define _CABBAGE_SCENE_CFRAMEBUFFEROBJECT_H_INCLUDED_

#include <GL/glew.h>
#include <map>
#include <ionTypes.h>

#include "CRenderBufferObject.h"
#include "CTexture.h"


class CFrameBufferObject
{

	GLuint Handle;

	std::map<u32, IRenderTarget *> ColorAttachments;
	IRenderTarget * DepthAttachment;

public:

	CFrameBufferObject();
	~CFrameBufferObject();

	void attach(CRenderBufferObject * RenderBufferObject, GLenum const Attachment);
	void attach(CTexture * Texture, GLenum const Attachment);

	GLuint const getHandle();

	void bind();
	void unbind();

	bool const isValid() const;

	std::map<u32, IRenderTarget *> const & getColorAttachments();
	IRenderTarget const * const getDepthAttachment();

};

void bindDeviceBackBuffer();

#endif
