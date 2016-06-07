#ifndef MOOSE_EVENT_LISTENER_HPP
#define MOOSE_EVENT_LISTENER_HPP

#include "Event.hpp"
#include "EventDispatcher.hpp"

#include <functional>

//A listening class that attaches itself to a listening object
//  that object can then use the notify method to tell a dispatcher
//  to queue and dispatch an event upon request.

class EXPORT EventDispatcher; //foward declaration

class EXPORT EventListener
{
public:
	EventListener() {}
	~EventListener(){}

	friend class EventDispatcher; //Gives event dispatcher the right to use OnNotify

	virtual void Register(EventDispatcher* ep, const std::function<void(Event)>& handler);
	//Register this listener to dispatcher ep with an event handler named handler

	virtual void Unregister(EventDispatcher* ep);
	//Unregister this listener from ep

	virtual void Notify(EventDispatcher* ep, Event evt);
	//Notify ep that evt just occured


private:
	virtual void OnNotify(Event evt) { this->handler(evt); }
	//Call the handler upon notification from the dispatcher

	std::function<void(Event)> handler;
	//Stores a pointer to the handling method that the listener is attached to

};

#endif