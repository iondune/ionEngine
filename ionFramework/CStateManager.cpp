#include "CStateManager.h"

#include "CApplication.h"
#include "CWindow.h"


CStateManager::CStateManager()
	: CurrentState(0)
{}

void CStateManager::SetState(IState * State)
{
	NextState = State;
}

void CStateManager::DoStateChange()
{
	if (! NextState)
		return;

	if (CurrentState)
		CurrentState->End();

	CurrentState = NextState;
	NextState = 0;

	CurrentState->Begin();
}

void CStateManager::Connect(CWindow * Window)
{
	Window->MouseEvent.AddChild(this);
	Window->KeyboardEvent.AddChild(this);
	Window->WindowResizedEvent.AddChild(this);
}

void CStateManager::ShutDown()
{
	if (CurrentState)
		CurrentState->End();

	CurrentState = 0;
}
