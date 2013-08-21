
#pragma once

#include <ionCore.h>


template <typename EventType>
class IEventListener : public ITreeNode<IEventListener<EventType>>
{

public:

	virtual void OnEvent(EventType & Event) = 0;

protected:

	void OnTriggered(EventType & Event)
	{
		OnEvent(Event);
		if (! Event.IsBlocked())
			for (auto Child : Children)
				Child->OnTriggered(Event);
		Event.Unblock();
	}

};
