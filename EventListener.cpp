#include "EventDispatcher.hpp"
#include "EventListener.hpp"

void EventListener::Notify(EventDispatcher* ep, Event evt)
{
	ep->QueueEvent(evt);
	ep->Dispatch(); //this is to be changed in the future for different types of dispatchers
					// the idea of dispatching here is to get rid of the necessity for globals
					// when wanting to do nested events.
}


void EventListener::Register(EventDispatcher* ep, const std::function<void(Event)>& handler)
{
	this->handler = handler;
	ep->RegisterListener(this);
}

void EventListener::Unregister(EventDispatcher* ep)
{
	ep->RemoveListener(this);
}