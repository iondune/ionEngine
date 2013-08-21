
#pragma once

#include <ionCore.h>
#include <ionMath.h>

#include "sigslot/sigslot.h"


class CApplication;

class CApplicationEventReceiver : public sigslot::has_slots<>
{

protected:

	CApplication * const Application;

public:

	CApplicationEventReceiver();

	virtual void OnKeyboardEvent(SKeyboardEvent const & Event);
	virtual void OnMouseEvent(SMouseEvent const & Event);

	virtual void OnGameTickStart(float const Elapsed);
	virtual void OnGameTickEnd(float const Elapsed);

	virtual void OnRenderStart(float const Elapsed);
	virtual void OnRenderEnd(float const Elapsed);

	virtual void OnWindowResized(SWindowResizedEvent const & Event);

	virtual void OnApplicationExit();

};

class CEventManager
{

    friend class CApplication;

    CEventManager();

	

public:	
	
    sigslot::signal1<SKeyboardEvent const &> OnKeyboardEvent;
    sigslot::signal1<SMouseEvent const &> OnMouseEvent;

    sigslot::signal1<float const> OnGameTickStart;
    sigslot::signal1<float const> OnGameTickEnd;

    sigslot::signal1<float const> OnRenderStart;
    sigslot::signal1<float const> OnRenderEnd;

	sigslot::signal1<SWindowResizedEvent const &> OnWindowResized;

    sigslot::signal0<> OnApplicationExit;

	

};
