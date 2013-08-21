
#pragma once


template <class TContext>
class CContextObject
{

protected:

	struct DisableAutoContextLoad
	{};

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
		Context = & TContext::get();
	}

};
