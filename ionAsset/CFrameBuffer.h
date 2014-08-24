
#pragma once

#include <ionGL.h>

#include "CTexture.h"
#include "CShader.h"


typedef ion::GL::Renderbuffer CRenderBuffer;

class CFrameBuffer : public ion::GL::Framebuffer
{

public:

	void MakeScreenSizedColorAttachment(u32 const Attachment);
	void MakeScreenSizedDepthTextureAttachment();

	void DrawColorAttachmentToScreen(u32 const Attachment);
	
	static void DrawTextureToScreen(CTexture2D * Texture);
	static ion::GL::IndexBuffer * GetQuadIndexBuffer();
	static ion::GL::VertexBuffer * GetQuadVertexBuffer();


private:
	
	static ion::GL::IndexBuffer * QuadIndexBuffer;
	static ion::GL::VertexBuffer * QuadVertexBuffer;

};
