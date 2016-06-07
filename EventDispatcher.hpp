#ifndef MOOSE_EVENT_DISPATCHER_HPP
#define MOOSE_EVENT_DISPATCHER_HPP

#include "EventListener.hpp"

#include <string>
#include <vector>
#include <queue>

//This dispatches all events to the cooresponding listeners upon Dispatch request

class EXPORT EventListener; //forward declaration

class EXPORT EventDispatcher
{
public:
	virtual ~EventDispatcher() {}

	void RegisterListener(EventListener* listener); 
	//Register a listener

	void RemoveListener(EventListener* listener);
	//Unregister a listener

	void Dispatch();
	//Dispatch all events in queue and remove them

	inline void QueueEmpty() {
	//Empty the queue with no dispatch
		for (int i = 0; !evtQueue.empty(); i++)
			evtQueue.pop();
	}

	inline void QueueEvent(Event evt) { evtQueue.push(evt); }
	//Queue a new event

	inline bool isEmpty() const { return evtQueue.empty(); }
	//Returns true if queue is empty false otherwise

	void DoNext();
	//Do next event


private:
	std::vector<EventListener*> listenerList; //List of all listeners
	std::queue<Event> evtQueue; //queue of events *
};

#endif