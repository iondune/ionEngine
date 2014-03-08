
#pragma once

#include <ionCore.h>
#include "IEvent.h"


class IEventListener : public ITreeNode<IEventListener>
{

public:

	virtual void OnEvent(IEvent & Event)
	{}

	void AddListener(IEventListener * Listener)
	{
		ITreeNode<IEventListener>::AddChild(Listener);
	}

	void RemoveListener(IEventListener * Listener)
	{
		ITreeNode<IEventListener>::RemoveChild(Listener);
	}

protected:

	using ITreeNode<IEventListener>::Children;

	void TriggerEvent(IEvent & Event)
	{
		OnEvent(Event);
		if (! Event.IsBlocked())
			for (auto it = Children.begin(); it != Children.end(); ++ it)
				(* it)->TriggerEvent(Event);
		Event.Unblock();
	}

};
