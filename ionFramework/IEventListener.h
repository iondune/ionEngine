
#pragma once

#include <ionCore.h>
#include "IEvent.h"


class IEventListener : public IMultiTreeNode<IEventListener>
{

public:

	virtual void OnEvent(IEvent & Event)
	{}

	void AddListener(IEventListener * Listener)
	{
		IMultiTreeNode<IEventListener>::AddChild(Listener);
	}

	void RemoveListener(IEventListener * Listener)
	{
		IMultiTreeNode<IEventListener>::RemoveChild(Listener);
	}

protected:

	using IMultiTreeNode<IEventListener>::Children;

	void TriggerEvent(IEvent & Event)
	{
		OnEvent(Event);
		if (! Event.IsBlocked())
			for (auto it = Children.begin(); it != Children.end(); ++ it)
				(* it)->TriggerEvent(Event);
		Event.Unblock();
	}

};
