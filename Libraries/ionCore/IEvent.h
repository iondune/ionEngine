
#pragma once


class IEvent
{

public:

	void Block()
	{
		Blocked = true;
	}

	void Unblock()
	{
		Blocked = false;
	}

	bool IsBlocked() const
	{
		return Blocked;
	}

	virtual ~IEvent()
	{}

protected:

	IEvent()
		: Blocked(false)
	{}

private:

	bool Blocked;

};
