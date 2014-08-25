
#pragma once

#include <ionGL.h>

#include "CTexture.h"
#include "CShader.h"


typedef ion::GL::Renderbuffer CRenderBuffer;

class CFrameBuffer
{

public:
	
	CFrameBuffer();
	CFrameBuffer(ion::GL::Framebuffer * Handle);

	void MakeScreenSizedColorAttachment(u32 const Attachment);
	void MakeScreenSizedDepthTextureAttachment();

	void DrawColorAttachmentToScreen(u32 const Attachment);

	void AttachColorTexture(CTexture2D * Texture, u32 const Attachment);
	void AttachDepthTexture(CTexture2D * Texture);
	void AttachDepthRenderBuffer(CRenderBuffer * RBO);

	CTexture2D * GetColorTextureAttachment(u32 const Attachment);
	CTexture2D * GetDepthTextureAttachment();

	void Clear(std::initializer_list<ion::GL::EBuffer> Buffers = { ion::GL::EBuffer::Color, ion::GL::EBuffer::Depth });

	ion::GL::Framebuffer * GetHandle();
	
	static void DrawTextureToScreen(CTexture2D * Texture);
	static ion::GL::IndexBuffer * GetQuadIndexBuffer();
	static ion::GL::VertexBuffer * GetQuadVertexBuffer();

	static CFrameBuffer * GetDefaultFrameBuffer();

private:

	ion::GL::Framebuffer * Handle = nullptr;
	
	static ion::GL::IndexBuffer * QuadIndexBuffer;
	static ion::GL::VertexBuffer * QuadVertexBuffer;

};
