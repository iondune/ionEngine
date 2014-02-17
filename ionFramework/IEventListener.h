
#pragma once

#include <ionCore.h>


template <typename EventType>
class IEventListener : public ITreeNode<IEventListener<EventType>>
{

public:

	virtual void OnEvent(EventType & Event) = 0;

protected:

	using ITreeNode<IEventListener<EventType>>::Children;

	void OnTriggered(EventType & Event)
	{
		OnEvent(Event);
		if (! Event.IsBlocked())
			for (auto it = Children.begin(); it != Children.end(); ++ it)
				(* it)->OnTriggered(Event);
		Event.Unblock();
	}

	void AddSubListener(IEventListener<EventType> * Listener)
	{
		AddChild(Listener);
	}

	void RemoveSubListener(IEventListener<EventType> * Listener)
	{
		RemoveChild(Listener);
	}

};
