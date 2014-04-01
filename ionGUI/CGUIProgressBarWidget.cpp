
#include <ionConfig.h>

#ifdef _ION_CONFIG_USE_GWEN

#include "CGUIProgressBarWidget.h"
#include "CGUIManager.h"


CGUIProgressBarWidget::CGUIProgressBarWidget(CGUIManager * Manager, std::string const & label)
	: CGUIWidget(Manager), Label(label), ProgressBar()
{}

void CGUIProgressBarWidget::Start()
{
	Window = new Gwen::Controls::WindowControl(GUIManager->GetCanvas());
	Window->SetClosable(false);
	Window->SetBounds(300, 300, 400, 150);
	Window->SetTitle("Loading...");
	Window->MakeModal(true);
	Window->SetMinimumSize(Gwen::Point(300, 150));

	Gwen::Controls::Label * LabelControl = new Gwen::Controls::Label(Window);
	LabelControl->SetFont(GUIManager->GetRegularFont());
	LabelControl->SetText(Gwen::UnicodeString(Label.begin(), Label.end()));
	LabelControl->SetBounds(10, 10, 600, 300);
	LabelControl->SetTextColor(Gwen::Color(35, 35, 55, 215));

	ProgressBar = new Gwen::Controls::ProgressBar(Window);
	ProgressBar->SetBounds(20, 50, 340, 40);
	ProgressBar->SetValue(0.5f);
}

void CGUIProgressBarWidget::Render()
{
	scopedLock Lock(ProgressMutex);

	if (ProgressBar)
		ProgressBar->SetValue(Progress);
}

void CGUIProgressBarWidget::Finish()
{
	scopedLock Lock(ProgressMutex);
	Window->DelayedDelete();
	ProgressBar = 0;
	Window = 0;
}

#endif
