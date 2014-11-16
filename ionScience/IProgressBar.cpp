
#include "IProgressBar.h"


void IProgressBar::CTask::Update(f64 const progress)
{
	Update((f32) progress);
}

void IProgressBar::CTask::Update(f32 const progress)
{
	if (Progress < progress)
	{
		Progress = progress;
		ProgressBar->SetProgress(Start + Value * Progress);
	}
}

IProgressBar::CTask::CTask(IProgressBar * ProgressBar, f32 const value, f32 const start)
	: Value(value), Start(start), Progress()
{
	this->ProgressBar = ProgressBar;
}

IProgressBar::IProgressBar()
	: Progress(), Started(false)
{}

void IProgressBar::BeginProgress()
{
	Progress = 0;
	Started = true;
	Start();
	Render();
}

void IProgressBar::SetProgress(f64 const progress)
{
	SetProgress((f32) progress);
}

void IProgressBar::SetProgress(f32 const progress)
{
	if (! Started)
		BeginProgress();

	if (Progress < progress)
	{
		Progress = progress;
		Render();
	}
}

void IProgressBar::EndProgress()
{
	Progress = 1;
	Render();
	Finish();

	Started = false;
}

IProgressBar::CTask * IProgressBar::NewTask(f32 const value)
{
	return new CTask(this, value, Progress);
}
