
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

	protected:

		CTask(f32 const value, f32 const start);

		IProgressBar * ProgressBar;
		f32 Value, Start, Progress;

	};

	void Begin();
	void Update(f32 const progress);
	void End();

	CTask * NewTask(f32 const value);

protected:
	
	virtual void Start() = 0;
	virtual void Render() = 0;
	virtual void Finish() = 0;

	f32 Progress;

};
