
#pragma once

#include <ionCore.h>


class IProgressBar
{

public:

	class CTask
	{

		friend class IProgressBar;

	public:
		
		void Update(f32 const progress);
		void Update(f64 const progress);

	protected:

		CTask(IProgressBar * ProgressBar, f32 const value, f32 const start);

		IProgressBar * ProgressBar = nullptr;
		f32 Value, Start, Progress;

	};

	void BeginProgress();
	void SetProgress(f32 const progress);
	void SetProgress(f64 const progress);
	void EndProgress();

	CTask * NewTask(f32 const value);

protected:

	IProgressBar();
	
	virtual void Start() = 0;
	virtual void Render() = 0;
	virtual void Finish() = 0;

	f32 Progress;
	bool Started;

};
