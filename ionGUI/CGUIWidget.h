
#pragma once

#include <ionCore.h>

#include "Gwen.h"


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
