
#pragma once


struct SEventData
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

protected:

	SEventData()
		: Blocked(false)
	{}

private:

	bool Blocked;

};
