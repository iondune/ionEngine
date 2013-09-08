
#include "IProgressBar.h"


void IProgressBar::CTask::Update(f32 const progress)
{
	if (Progress < progress)
	{
		Progress = progress;
		ProgressBar->Update(Start + Value * Progress);
	}
}

IProgressBar::CTask::CTask(f32 const value, f32 const start)
	: Value(value), Start(start), Progress()
{}

void IProgressBar::Begin()
{
	Progress = 0;
	Start();
	Render();
}

void IProgressBar::Update(f32 const progress)
{
	if (Progress < progress)
	{
		Progress = progress;
		Render();
	}
}

void IProgressBar::End()
{
	Progress = 1;
	Render();
	Finish();
}

IProgressBar::CTask * IProgressBar::NewTask(f32 const value)
{
	return new CTask(value, Progress);
}
