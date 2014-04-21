
#pragma once

#include "IState.h"
#include "CApplication.h"
#include "CWindowManager.h"


struct NullContext : public Singleton<NullContext>
{};

template <class TImplementation, class TContext = NullContext>
class CContextState : public IState, public Singleton<TImplementation>
{

protected:
	
	SingletonPointer<CApplication> Application;
	SingletonPointer<CWindowManager> WindowManager;
	SingletonPointer<TContext> Context;

};
