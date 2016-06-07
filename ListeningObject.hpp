#ifndef LISTENING_OBJECT_HPP
#define LISTENING_OBJECT_HPP


#include "Event.hpp"
#include "EventDispatcher.hpp"
#include "EventListener.hpp"

//This is a listening object for the event classes.
//This simply holds all the methods needed for effectively
// using the EventListener and EventDispatcher

class EXPORT ListeningObject
{
public:
	virtual ~ListeningObject() {}

	void RegisterListener(EventDispatcher* ed){
		std::function<void(Event)> handlerBind = std::bind(&ListeningObject::OnEvent, this, std::placeholders::_1);
		listener.Register(ed, handlerBind);
	}

	void UnregisterListener(EventDispatcher* ed){
		ed->RemoveListener(&this->listener);
	}

	virtual void OnEvent(Event evt) {}

protected:
	EventListener listener;
};

#endif
