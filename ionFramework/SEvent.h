
#pragma once

#include <ionCore.h>

#include "ICallable.h"


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

template <typename EventType>
class IEventListener : public ITreeNode<IEventListener>
{

public:

	void OnTriggered(EventType & Event)
	{
		OnEvent(Event);
		if (! Event.IsBlocked())
			for (auto Child : Children)
				Child->OnTriggered(Event);
		Event.Unblock();
	}

	virtual void OnEvent(EventType & Event) = 0;

};

template <typename EventType>
struct SEvent : public IEventListener
{

	static_assert(std::is_base_of<SEventData, EventType>, "SEventData must be a base of event type.");

	class ITrigger
	{

	public:

		~ITrigger()
		{
			for (auto it = Events.begin(); it != Events.end();)
			{
				SEvent * Event = * it;
				it = Events.erase(it);
				Event->RemoveTrigger(this);
			}
		}

		void Trigger(EventType & Event)
		{
			for (auto Event : Events)
			{
				Event.OnTriggered(Event);
			}
		}

	protected:

		std::set<sharedPtr<SEvent<EventType>>> Events;

	};

	void OnEvent(EventType & Event)
	{}

public:

	void RemoveTrigger(ITrigger<EventType> * Trigger)
	{
		Triggers.erase(Trigger);
		Trigger->Events.erase(this);
	}

	void RemoveAllTriggers()
	{
		for (auto Trigger : Triggers)
			Trigger->Events.erase(this);
		Triggers.clear();
	}

	void AddTrigger(sharedPtr<ITrigger<EventType>> Trigger)
	{
		Triggers.insert(Trigger);
		Trigger->Events.insert(this);
	}

protected:
	
	std::set<sharedPtr<ITrigger<EventType>>> Triggers;

};
