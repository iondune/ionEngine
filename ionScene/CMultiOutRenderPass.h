#ifndef _ION_SCENE_CMULTIOUTRENDERPASS_H_INCLUDED_
#define _ION_SCENE_CMULTIOUTRENDERPASS_H_INCLUDED_

#include "IRenderPass.h"
#include <ionGraphics/CFrameBufferObject.h>


class CMultiOutRenderPass : public IRenderPass
{

protected:

	CFrameBufferObject * FrameBuffer;

public:

	CMultiOutRenderPass()
		: FrameBuffer(0)
	{}

	virtual void onPreDraw()
	{
		if (FrameBuffer)
		{
			FrameBuffer->bind();

			for (auto it = FrameBuffer->getColorAttachments().begin(); it != FrameBuffer->getColorAttachments().end(); ++ it)
			{
				color4f const Color = Colors::White;
				glClearBufferfv(GL_COLOR, it->first, Color.GetValuePointer());
			}

			if (FrameBuffer->getDepthAttachment())
			{
				glClearBufferfv(GL_DEPTH, 0, Colors::White.GetValuePointer());
			}
		}
		else
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
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
