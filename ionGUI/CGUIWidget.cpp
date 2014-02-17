
#ifdef _ION_CONFIG_USE_GWEN

#include "CGUIManager.h"


CGUIWidget::CGUIWidget(CGUIManager * Manager)
	: GUIManager(Manager)
{
	GUIManager->AddWidget(this);
}

CGUIWidget::~CGUIWidget()
{}

void CGUIWidget::Update(float const Elapsed)
{}

#endif
