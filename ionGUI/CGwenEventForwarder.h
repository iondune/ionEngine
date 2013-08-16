
#pragma once

#include <ionWindow.h>
#include <Gwen/Events.h>
#include <Gwen/Controls.h>


class CGwenEventForwarder : public CApplicationEventReceiver
{

	Gwen::Controls::Canvas * Canvas;
	std::function<void (SMouseEvent const &)> OnUncaughtMouseEvent;

public:

	CGwenEventForwarder(Gwen::Controls::Canvas * pCanvas, std::function<void (SMouseEvent const &)> onUncaughtMouseEvent);

	virtual void OnKeyboardEvent(SKeyboardEvent const & Event);

	virtual void OnMouseEvent(SMouseEvent const & Event);

	virtual void OnGameTickStart(float const Elapsed);
	virtual void OnGameTickEnd(float const Elapsed);

	virtual void OnRenderStart(float const Elapsed);
	virtual void OnRenderEnd(float const Elapsed);

	virtual void OnApplicationExit();

};
