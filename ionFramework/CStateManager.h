
#pragma once

#include "IState.h"


namespace ion
{

	class CWindow;

	class CStateManager : public Singleton<CStateManager>, public IEventListener
	{

		friend class Singleton<CStateManager>;

	public:

		void SetState(IState * State);
		void DoStateChange();

		void Update(f32 const ElapsedTime);

		void Connect(CWindow * Window);
		void ShutDown();

	private:

		CStateManager();

	protected:

		IState * CurrentState = nullptr;
		IState * NextState = nullptr;

	};

}
