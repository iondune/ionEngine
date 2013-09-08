
#pragma once

#include "Gwen.h"
#include "CGUIWidget.h"

#include <ionScience\IProgressBar.h>


class CGUIProgressBarWidget : public CGUIWidget, public IProgressBar
{

public:

	CGUIProgressBarWidget(CGUIManager * Manager, std::string const & label);

protected:
	
	void Start();
	void Render();
	void Finish();

	Gwen::Controls::WindowControl * Window;
	Gwen::Controls::ProgressBar * ProgressBar;
	
	std::string Label;

	mutex ProgressMutex;

};
