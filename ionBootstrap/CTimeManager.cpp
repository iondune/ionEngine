
#include "CTimeManager.h"
#include <GLFW/glfw3.h>


void CTimeManager::Init()
{
	LastTime = glfwGetTime();
	RunTime = ElapsedTime = 0.f;
}

void CTimeManager::UpdateTime()
{
	f64 NewTime = glfwGetTime();
	ElapsedTime = NewTime - LastTime;
	RunTime += ElapsedTime;
	LastTime = NewTime;
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

CTimeManager::CTimeManager()
{}
