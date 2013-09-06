
#pragma once

#include <ionCore/ionTypes.h>
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

	virtual void Update(f32 const Elapsed);

};
