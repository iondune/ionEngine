#ifndef _CABBAGEGUI_CGUIENGINE_H_INCLUDED_
#define _CABBAGEGUI_CGUIENGINE_H_INCLUDED_

// STD / STL
#include <vector>

// Other Libraries
#include <sigslot/sigslot.h>

// Cabbage
#include <SPosition2.h>
#include <CEventManager.h>

// Local
#include "CGUIWidget.h"


class CGUIEventManager
{

public:

	sigslot::signal1<CGUIWidget *> OnWidgetHover;
	sigslot::signal1<CGUIWidget *> OnWidgetUnHover;
	sigslot::signal1<CGUIWidget *> OnWidgetClick;

};

class CGUIEngine;

class CGUIEventReceiver : public sigslot::has_slots<>
{

protected:

	CGUIEngine * const GUIEngine;
   int connected;

public:

	CGUIEventReceiver();

	virtual ~CGUIEventReceiver();

	virtual void OnWidgetHover(CGUIWidget * Widget);
	virtual void OnWidgetUnHover(CGUIWidget * Widget);
	virtual void OnWidgetClick(CGUIWidget * Widget);

   void connect();
   void disconnect();

};

class CGUIEngine : public CApplicationEventReceiver
{

	std::vector<CGUIWidget *> Widgets;

	SPosition2 const ScreenSize;

	CGUIEventManager EventManager;

public:

	CGUIEngine(SPosition2 const & screenSize);

	void addWidget(CGUIWidget * Widget);
	void removeWidget(CGUIWidget * Widget);
	void removeAllWidgets();
    bool isWidgetIn(CGUIWidget * Widget);

	void drawAll();

	CGUIEventManager * const getEventManager();
	CGUIEventManager const * const getEventManager() const;

	void OnMouseEvent(SMouseEvent const & Event);

};

#endif
