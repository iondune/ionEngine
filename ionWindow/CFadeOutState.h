#ifndef _ION_FRAMEKWORK_CFADEOUTSTATE_H_INCLUDED_
#define _ION_FRAMEKWORK_CFADEOUTSTATE_H_INCLUDED_

#include "CStateManager.h"
#include <CFrameBufferObject.h>
#include <CTexture.h>

class CFadeOutState : public IState
{

	/*CApplication & Application;
	CSceneManager & SceneManager;
	CGUIEngine & GUIEngine;*/

	CFrameBufferObject * SourceFrameBuffer;
	CTexture * SourceFrameTexture;

	float TotalRunTime;
	float FadeTime;

	IState * NextState;

public:

	CFadeOutState(IState * nextState, float const fadeTime = 0.3f);

    virtual void begin();

    virtual void end();


    virtual void OnGameTickStart(float const Elapsed);

    virtual void OnGameTickEnd(float const Elapsed);


    virtual void OnRenderStart(float const Elapsed);

    virtual void OnRenderEnd(float const Elapsed);


    virtual void OnMouseEvent(SMouseEvent const & Event);

    virtual void OnKeyboardEvent(SKeyboardEvent const & Event);

};

#endif
