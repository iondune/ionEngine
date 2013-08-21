
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

template <typename EventType>
struct SEvent : public IEventListener<EventType>, public std::enable_shared_from_this<SEvent<EventType>>
{

	static_assert(std::is_base_of<SEventData, EventType>::value, "SEventData must be a base of event type.");

	class ITrigger : public std::enable_shared_from_this<ITrigger>
	{

	public:

		~ITrigger()
		{
			for (auto it = Events.begin(); it != Events.end();)
			{
				sharedPtr<SEvent> Event = * it;
				it = Events.erase(it);
				Event->RemoveTrigger(shared_from_this());
			}
		}

		void Trigger(EventType & EventData)
		{
			for (auto Event : Events)
			{
				Event->OnTriggered(EventData);
			}
		}

	protected:

		friend struct SEvent<EventType>;
		std::set<sharedPtr<SEvent<EventType>>> Events;

	};

	void OnEvent(EventType & Event)
	{}

public:

	void RemoveTrigger(sharedPtr<ITrigger> const Trigger)
	{
		Triggers.erase(Trigger);
		Trigger->Events.erase(shared_from_this());
	}

	void RemoveAllTriggers()
	{
		for (auto Trigger : Triggers)
			Trigger->Events.erase(shared_from_this());
		Triggers.clear();
	}

	void AddTrigger(sharedPtr<ITrigger> Trigger)
	{
		Triggers.insert(Trigger);
		Trigger->Events.insert(this);
	}

protected:
	
	std::set<sharedPtr<ITrigger>> Triggers;

};