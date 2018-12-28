
#include "CTimeManager.h"
#include <GLFW/glfw3.h>


namespace ion
{

	double CTimeManager::CUpdateTick::GetTick() const
	{
		return Tick;
	}

	double CTimeManager::CUpdateTick::GetElapsedTime() const
	{
		return Tick;
	}

	double CTimeManager::CUpdateTick::GetMaxDuration() const
	{
		return MaxDuration;
	}

	double CTimeManager::CUpdateTick::GetAccumulator() const
	{
		return Accumulator;
	}

	CTimeManager::CUpdateTick::CUpdateTick(double const Duration, double const MaxDuration)
	{
		this->Tick = Duration;
		this->MaxDuration = MaxDuration;
		this->Accumulator = 0;
	}

	void CTimeManager::CUpdateTick::Update(double const Elapsed)
	{
		Accumulator = Minimum(Accumulator + Elapsed, MaxDuration);

		while (Accumulator > Tick)
		{
			Accumulator -= Tick;
			TriggerEvent(* this);
		}
	}

	void CTimeManager::Init(CWindowManager * WindowManager)
	{
		Start();
	}

	void CTimeManager::Start()
	{
		LastTime = glfwGetTime();
	}

	void CTimeManager::Update()
	{
		double NewTime = glfwGetTime();
		ElapsedTime = (NewTime - LastTime) * TimeMultiplier;
		RunTime += ElapsedTime;
		LastTime = NewTime;

		for (auto & UpdateTick : UpdateTicks)
			UpdateTick->Update(ElapsedTime);
	}

	void CTimeManager::SkipElapsedTime()
	{
		LastTime = glfwGetTime();
	}

	double CTimeManager::GetElapsedTime() const
	{
		return ElapsedTime;
	}

	double CTimeManager::GetActualElapsedTime() const
	{
		return ElapsedTime / TimeMultiplier;
	}

	double CTimeManager::GetRunTime() const
	{
		return RunTime;
	}

	double CTimeManager::GetTimeMultiplier() const
	{
		return TimeMultiplier;
	}

	void CTimeManager::SetTimeMultiplier(double const TimeMultiplier)
	{
		this->TimeMultiplier = TimeMultiplier;
	}

	CTimeManager::CUpdateTick * CTimeManager::MakeUpdateTick(double const Tick, double const MaxDuration)
	{
		UpdateTicks.push_back(new CUpdateTick{ Tick, MaxDuration });
		return UpdateTicks.back();
	}

	CTimeManager::CTimeManager()
	{
	}

	CStopWatch::CStopWatch()
	{
		Start();
	}

	double CStopWatch::Start()
	{
		return t0 = glfwGetTime();
	}

	double CStopWatch::Stop()
	{
		double const t1 = glfwGetTime();
		return t1 - t0;
	}

}
