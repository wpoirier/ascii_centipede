//manager.cpp

#include "manager.h"
#include "objectlistiterator.h"
#include "eventstep.h"
#include "eventout.h"
#include "eventkeyboard.h"
#include "eventmouse.h"
#include "eventcollision.h"

#include "logmanager.h"

Manager::Manager() {
	//initialize event list to be empty (null)
	
	for (int i = 0; i < MAX_EVENTS; i++) {
		elist[i] = "\0";
	}
	this->event_list_count = 0;
	
}

Manager::~Manager() {}

int Manager::startUp() {}

int Manager::shutDown() {}

//Register manager's interest in *object for event_name
//Return 0 for success, else -1
int Manager::registerInterest(Object *p_o, string event_name) {

	//Error, list is full
	if (event_list_count >= MAX_EVENTS) return -1; 

	//Error, Manager doesn't handle this event
	if(!isValid(event_name)) return -1; 

	//***IF THIS EVENT HAS BEEN ALREADY ADDED***
	//for i = 0 to event_list_count)
	for (int i = 0; i <= event_list_count; i++) {  
	if (elist[i] == event_name) {//if this event already exists
		objInterest[i].insert(p_o); //insert object into list
		return 0;
		}
	}

	//***IF THIS IS A NEW EVENT***
	elist[event_list_count] = event_name;
	objInterest[event_list_count].insert(p_o);
	event_list_count++;
 
 return 0;	
}

//Unregister manager's interest in event.
//Return 0 for success, else -1
int Manager::unregisterInterest(Object *p_o, string event_name) {
	LogManager &lm = LogManager::getInstance();
	lm.writeLog("Manager::unregisterInterest()");
	for (int i = 0; i <= event_list_count; i++) {
		if (elist[i] == event_name) {
			objInterest[i].remove(p_o);
	
			if (objInterest[i].list[0] == NULL) { // list empty
				for (int j = i; j < event_list_count - 1; j++) {
					objInterest[i] = objInterest[i + 1];
					elist[i] = elist[i + 1];
				}
				event_list_count--;
			}
			return 0; // object successfully unregistered
		}
	
	}
	return -1; //object not found 
}

//Send event to all interested objects
void Manager::onEvent(Event *p_event) {

	LogManager &lm = LogManager::getInstance();
	lm.writeLog("*Event p_event == %s", p_event->getType().c_str());
	lm.writeLog("Event List Count: %d", event_list_count);

	for (int i = 0; i < event_list_count; i++) {
		if (elist[i] == p_event->getType()) {
			lm.writeLog("elist[%d] == %s", i, elist[i].c_str());
			const ObjectList * objint = &objInterest[i];
			ObjectListIterator *it = new ObjectListIterator(objint);
			while (!it->isDone()) {
				lm.writeLog("it->currentItem() == %p", it->currentItem());
				it->currentItem()->eventHandler(p_event);
				it->next();
			}
		}
	}
}

bool Manager::isValid(string event_name) {
	return false;
}
