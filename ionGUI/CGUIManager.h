
#pragma once

#include <ionCore.h>
#include <ionWindow.h>

#include "CGUIWidget.h"


class CApplication;

class CGUIManager : public Singleton<CGUIManager>
{

public:

	void Init(string const & Skin = "DefaultSkin.png");
	void Draw(f32 const Elapsed, bool ClearAll = false);

	Gwen::Controls::Canvas * GetCanvas();
	
	Gwen::Font * GetLargeFont();
	Gwen::Font * GetMediumFont();
	Gwen::Font * GetRegularFont();
	
	void AddWidget(CGUIWidget * Widget);
	void RemoveWidget(CGUIWidget * Widget);
	void RemoveAllWidgets();

protected:
	
	SingletonPointer<CWindowManager> WindowManager;

	Gwen::Controls::Canvas * Canvas;
	
	Gwen::Font * LargeFont;
	Gwen::Font * MediumFont;
	Gwen::Font * RegularFont;

	std::vector<CGUIWidget *> Widgets;

private:
	
	friend class Singleton<CGUIManager>;
	CGUIManager();

};
