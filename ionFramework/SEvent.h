
#pragma once

#include <ionCore.h>

#include "SEventData.h"
#include "IEventListener.h"


template <typename EventType>
struct SEvent : public IEventListener<EventType>
{

	static_assert(std::is_base_of<SEventData, EventType>::value, "SEventData must be a base of event type.");

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

		void Trigger(EventType & EventData)
		{
			for (auto Event : Events)
			{
				Event->OnTriggered(EventData);
			}
		}

	protected:

		friend struct SEvent<EventType>;
		std::set<SEvent<EventType> *> Events;

	};

	void OnEvent(EventType & Event)
	{}

public:

	void RemoveTrigger(ITrigger * Trigger)
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

	void AddTrigger(ITrigger * Trigger)
	{
		Triggers.insert(Trigger);
		Trigger->Events.insert(this);
	}

protected:
	
	std::set<ITrigger *> Triggers;

};
