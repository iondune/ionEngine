#include "CStateManager.h"

#include "CApplication.h"
#include <ionWindow/CWindow.h>


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
		IEventListener<SMouseEvent>::RemoveChild(CurrentState);
		IEventListener<SKeyboardEvent>::RemoveChild(CurrentState);
		IEventListener<SWindowResizedEvent>::RemoveChild(CurrentState);
		CurrentState->End();
	}

	CurrentState = NextState;
	NextState = 0;

	CurrentState->Begin();
	IEventListener<SMouseEvent>::AddChild(CurrentState);
	IEventListener<SKeyboardEvent>::AddChild(CurrentState);
	IEventListener<SWindowResizedEvent>::AddChild(CurrentState);
}

void CStateManager::Update(f32 const ElapsedTime)
{
	if (CurrentState)
		CurrentState->Update(ElapsedTime);
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
