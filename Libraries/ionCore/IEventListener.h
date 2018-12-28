
#pragma once

#include "IMultiTreeNode.h"
#include "IEvent.h"


class IEventListener : public ion::IMultiTreeNode<IEventListener>
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

	void TriggerEvent(IEvent & Event)
	{
		OnEvent(Event);
		if (! Event.IsBlocked())
			for (auto it = Children.begin(); it != Children.end(); ++ it)
				(* it)->TriggerEvent(Event);
		Event.Unblock();
	}

protected:

	using IMultiTreeNode<IEventListener>::Children;

};
