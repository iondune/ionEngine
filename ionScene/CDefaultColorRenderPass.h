#ifndef _ION_SCENE_CDEFAULTCOLORRENDERPASS_H_INCLUDED_
#define _ION_SCENE_CDEFAULTCOLORRENDERPASS_H_INCLUDED_

#include "IRenderPass.h"
#include "CFrameBufferObject.h"


class CDefaultColorRenderPass : public IRenderPass
{

protected:

	CFrameBufferObject * FrameBuffer;

public:

	CDefaultColorRenderPass()
		: FrameBuffer(0)
	{}

	CDefaultColorRenderPass(CFrameBufferObject * frameBuffer)
		: FrameBuffer(frameBuffer)
	{}

	virtual void onPreDraw()
	{
		if (FrameBuffer)
			FrameBuffer->bind();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	virtual void onPostDraw()
	{
		if (FrameBuffer)
			FrameBuffer->unbind();
	}

	virtual void onPreDrawObject(ISceneObject * Object)
	{}

	virtual void onPostDrawObject(ISceneObject * Object)
	{}

	CFrameBufferObject const * const getFrameBuffer() const
	{
		return FrameBuffer;
	}

	CFrameBufferObject * const getFrameBuffer()
	{
		return FrameBuffer;
	}

	void setFrameBuffer(CFrameBufferObject * frameBuffer)
	{
		FrameBuffer = frameBuffer;
	}

};

#endif
