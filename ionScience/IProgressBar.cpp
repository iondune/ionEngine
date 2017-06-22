
#include "IProgressBar.h"


namespace ion
{

	void IProgressBar::CTask::Update(double const progress)
	{
		Update((float) progress);
	}

	void IProgressBar::CTask::Update(float const progress)
	{
		if (Progress < progress)
		{
			Progress = progress;
			ProgressBar->SetProgress(Start + Value * Progress);
		}
	}

	IProgressBar::CTask::CTask(IProgressBar * ProgressBar, float const value, float const start)
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

	void IProgressBar::SetProgress(double const progress)
	{
		SetProgress((float) progress);
	}

	void IProgressBar::SetProgress(float const progress)
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

	IProgressBar::CTask * IProgressBar::NewTask(float const value)
	{
		return new CTask(this, value, Progress);
	}

}
