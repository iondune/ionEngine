
#pragma once

#include <ionTypes.h>
#include <ionWindow.h>

#include <Gwen/Controls.h>


class CGUIManager;

class CGUIWidget : public Gwen::Event::Handler
{

protected:

	CGUIManager * GUIManager;

public:

	CGUIWidget(CGUIManager * Manager);
	virtual ~CGUIWidget();

	virtual void update(f32 const Elapsed);

};