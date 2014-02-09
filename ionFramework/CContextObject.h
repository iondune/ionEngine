
#pragma once


struct DisableAutoContextLoad
{};

template <class TContext>
class CContextObject
{

protected:

	TContext * Context;

	CContextObject()
		: Context()
	{
		LoadContext();
	}

	CContextObject(DisableAutoContextLoad)
		: Context()
	{}

public:

	virtual void LoadContext()
	{
		Context = TContext::GetPtr();
	}

};
