
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
