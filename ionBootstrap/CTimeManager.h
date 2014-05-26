
#pragma once

#include <ionCore.h>


class CTimeManager : public Singleton<CTimeManager>
{

public:

	void Init();

	void UpdateTime();
	void SkipElapsedTime();
	f64 GetElapsedTime() const;
	f64 GetRunTime() const;

protected:

	f64 ElapsedTime;
	f64 RunTime;
	f64 LastTime;

private:

	friend class Singleton<CTimeManager>;
	CTimeManager();

};
