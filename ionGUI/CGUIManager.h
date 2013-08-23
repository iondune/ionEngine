
#pragma once

#include <ionTypes.h>
#include <ionWindow.h>
#include <ionFramework.h>

#include <Gwen/Controls.h>

#include "CGUIWidget.h"


class CApplication;

class CGUIManager
{

protected:

	CApplication & Application;

	Gwen::Controls::Canvas * Canvas;
	
	Gwen::Font * LargeFont;
	Gwen::Font * MediumFont;
	Gwen::Font * RegularFont;

	std::vector<CGUIWidget *> Widgets;

public:

	CGUIManager();

	void init();
	void draw(f32 const Elapsed, bool ClearAll = false);

	Gwen::Controls::Canvas * getCanvas();
	
	Gwen::Font * getLargeFont();
	Gwen::Font * getMediumFont();
	Gwen::Font * getRegularFont();
	
	void addWidget(CGUIWidget * Widget);
	void removeWidget(CGUIWidget * Widget);
	void removeAllWidgets();

};
