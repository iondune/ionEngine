#include "CStateManager.h"

#include "CApplication.h"
#include "CWindow.h"


void CStateManager::SetState(IState * State)
{
	NextState = State;
}

void CStateManager::DoStateChange()
{
	if (! NextState)
		return;

	if (CurrentState)
	{
		RemoveListener(CurrentState);
		CurrentState->End();
	}

	CurrentState = NextState;
	NextState = 0;

	CurrentState->Begin();
	AddListener(CurrentState);;
}

void CStateManager::Update(f32 const ElapsedTime)
{
	if (CurrentState)
		CurrentState->Update(ElapsedTime);
}

void CStateManager::Connect(CWindow * Window)
{
	Window->AddListener(this);
}

void CStateManager::ShutDown()
{
	if (CurrentState)
		CurrentState->End();

	CurrentState = 0;
}

void CStateManager::OnEvent(SMouseEvent & Event)
{
}

void CStateManager::OnEvent(SKeyboardEvent & Event)
{
}

void CStateManager::OnEvent(SWindowResizedEvent & Event)
{
}

CStateManager::CStateManager()
	: CurrentState(0)
{}
