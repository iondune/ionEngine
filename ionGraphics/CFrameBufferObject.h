
#pragma once

#include <GL/glew.h>
#include <map>
#include <ionCore/ionTypes.h>

#include "CRenderBufferObject.h"
#include "CTexture.h"


class CFrameBufferObject
{

	GLuint Handle;

	std::map<u32, CTexture *> ColorAttachments;
	IRenderTarget * DepthAttachment;

public:

	CFrameBufferObject();
	~CFrameBufferObject();

	void attachColorTexture(CTexture * Texture, u32 const Attachment);
	void attachDepthTexture(CTexture * Texture);
	void attachDepthRenderBuffer(CRenderBufferObject * RenderBufferObject);

	GLuint const getHandle();

	void bind();
	void unbind();

	bool const isValid() const;

	std::map<u32, CTexture *> const & getColorAttachments();
	IRenderTarget const * const getDepthAttachment();
	
	static void bindDeviceBackBuffer();

};
