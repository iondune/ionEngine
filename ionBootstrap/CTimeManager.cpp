
#include "CTimeManager.h"
#include <GLFW/glfw3.h>



f64 CTimeManager::CUpdateTick::GetTick() const
{
	return Tick;
}

f64 CTimeManager::CUpdateTick::GetElapsedTime() const
{
	return Tick;
}

f64 CTimeManager::CUpdateTick::GetMaxDuration() const
{
	return MaxDuration;
}

f64 CTimeManager::CUpdateTick::GetAccumulator() const
{
	return Accumulator;
}

CTimeManager::CUpdateTick::CUpdateTick(f64 const Duration, f64 const MaxDuration)
{
	this->Tick = Duration;
	this->MaxDuration = MaxDuration;
	this->Accumulator = 0;
}

void CTimeManager::CUpdateTick::Update(f64 const Elapsed)
{
	Accumulator = Min(Accumulator + Elapsed, MaxDuration);

	while (Accumulator > Tick)
	{
		Accumulator -= Tick;
		TriggerEvent(* this);
	}
}

void CTimeManager::Init()
{
	LastTime = glfwGetTime();
	RunTime = ElapsedTime = 0;
	TimeMultiplier = 1;
}

void CTimeManager::Update()
{
	f64 NewTime = glfwGetTime();
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

f64 CTimeManager::GetElapsedTime() const
{
	return ElapsedTime;
}

f64 CTimeManager::GetRunTime() const
{
	return RunTime;
}

f64 CTimeManager::GetTimeMultiplier() const
{
	return TimeMultiplier;
}

void CTimeManager::SetTimeMultiplier(f64 const TimeMultiplier)
{
	this->TimeMultiplier = TimeMultiplier;
}

CTimeManager::CUpdateTick * CTimeManager::MakeUpdateTick(f64 const Tick, f32 const MaxDuration)
{
	UpdateTicks.push_back(new CUpdateTick{Tick, MaxDuration});
	return UpdateTicks.back();
}

CTimeManager::CTimeManager()
{
}
