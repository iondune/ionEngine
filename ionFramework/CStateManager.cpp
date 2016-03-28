
#include "CStateManager.h"


namespace ion
{

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
		AddListener(CurrentState);
	}

	void CStateManager::Update(f32 const ElapsedTime)
	{
		if (CurrentState)
			CurrentState->Update(ElapsedTime);
	}

	void CStateManager::ShutDown()
	{
		if (CurrentState)
			CurrentState->End();

		CurrentState = 0;
	}

	CStateManager::CStateManager()
	{}

}
