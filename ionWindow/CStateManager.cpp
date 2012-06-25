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
		CurrentState->disconnect();
		if (& CApplication::get().getGUIEngine())
			CApplication::get().getGUIEngine().removeAllWidgets();
		if (& CApplication::get().getSceneManager())
		{
			CApplication::get().getSceneManager().Lights.clear();
			CApplication::get().getSceneManager().removeAllSceneObjects();
		}
		CurrentState->end();
	}

	CurrentState = NextState;
	NextState = NULL;

	CurrentState->connect();
	CurrentState->begin();

	CApplication::get().getSceneManager().blurSceneIn(0.3f, CApplication::get().getRunTime());
}

void CStateManager::shutDown()
{
	if (CurrentState)
		CurrentState->end();

	CurrentState = 0;
}
