
#pragma once

#include <ionCore.h>
#include <ionWindow.h>

#include "CGUIWidget.h"


class CApplication;

class CGUIManager : public Singleton<CGUIManager>
{

public:

	void Init(string const & Skin, string const & FontFile);
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

	Gwen::Controls::Canvas * Canvas = nullptr;
	
	Gwen::Font * LargeFont = nullptr;
	Gwen::Font * MediumFont = nullptr;
	Gwen::Font * RegularFont = nullptr;

	std::vector<CGUIWidget *> Widgets;

	bool Initialized = false;

private:
	
	friend class Singleton<CGUIManager>;
	CGUIManager();

};
