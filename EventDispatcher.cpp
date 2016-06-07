#include "EventDispatcher.hpp"
#include "EventListener.hpp"
#include <string>

void EventDispatcher::DoNext()
{
	Event evt = evtQueue.front();
	evtQueue.pop();
	
	for (unsigned int i = 0; i < listenerList.size(); i++)
	{
		if (!listenerList[i] == NULL)    //just incase something happens, since
			listenerList[i]->OnNotify(evt); // I'm not using shared pointers
		else
			break;
	}

}

void EventDispatcher::Dispatch()
{
	while (!evtQueue.empty())
		DoNext();
}

void EventDispatcher::RemoveListener(EventListener* listener)
{
	for (unsigned int i = 0; i < listenerList.size(); i++)
		if (listenerList[i] == listener)
			listenerList.pop_back();
}

void EventDispatcher::RegisterListener(EventListener* listener) 
{
	for (unsigned int i = 0; i < listenerList.size(); i++)
		if (listenerList[i] == listener)
		{
			std::cout << "Listener already added" << std::endl;
			return;
		}

	listenerList.push_back(listener); 
}