
#pragma once

#include "CApplicationContextObject.h"


struct NullContext : public Singleton<NullContext>
{};

template <class TImplementation, class TContext = NullContext>
class CContextState : public IState, public Singleton<TImplementation>, public CApplicationContextObject<TContext>
{

protected:

	CContextState()
	{}

	CContextState(DisableAutoContextLoad)
		: CApplicationContextObject<TContext>(DisableAutoContextLoad)
	{}

};
