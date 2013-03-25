#include "CStateManager.h"

#include "CApplication.h"


CStateManager::CStateManager()
	: CurrentState(0)
{}

void CStateManager::OnGameTickStart(float const Elapsed)
{
	if (CurrentState)
		CurrentState->OnGameTickStart(Elapsed);
}

void CStateManager::OnGameTickEnd(float const Elapsed)
{
	if (CurrentState)
		CurrentState->OnGameTickEnd(Elapsed);
}


void CStateManager::OnRenderStart(float const Elapsed)
{
	if (CurrentState)
		CurrentState->OnRenderStart(Elapsed);
}

void CStateManager::OnRenderEnd(float const Elapsed)
{
	if (CurrentState)
		CurrentState->OnRenderEnd(Elapsed);
}


void CStateManager::OnMouseEvent(SMouseEvent const & Event)
{
	if (CurrentState)
		CurrentState->OnMouseEvent(Event);
}

void CStateManager::OnKeyboardEvent(SKeyboardEvent const & Event)
{
	if (CurrentState)
		CurrentState->OnKeyboardEvent(Event);
}


void CStateManager::OnSFMLEvent(sf::Event const & Event)
{
	if (CurrentState)
		CurrentState->OnSFMLEvent(Event);
}

void CStateManager::OnWindowResized(SWindowResizedEvent const & Event)
{
	if (CurrentState)
		CurrentState->OnWindowResized(Event);
}

void CStateManager::setState(IState * State)
{
	NextState = State;
}

void CStateManager::doStateChange()
{
	if (! NextState)
		return;

	if (CurrentState)
	{
		CurrentState->end();
	}

	CurrentState = NextState;
	NextState = NULL;

	CurrentState->begin();
}

void CStateManager::shutDown()
{
	if (CurrentState)
		CurrentState->end();

	CurrentState = 0;
}
