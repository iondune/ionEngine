
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

private:

	bool Blocked;

};
