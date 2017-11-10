#ifndef __MANAGER_H__
#define __MANAGER_H__

#include "objectlist.h"
#include "event.h"
#include <string>

class Manager {

private:

	int event_list_count; //number of events
	string elist[MAX_EVENTS]; //list of events
	ObjectList objInterest[MAX_EVENTS]; //object list of interested objects

	/*isValid Temporarily commented out! Put back in when needed!!!*/
protected:

	//Check of event is handled by this manager
	//Return true if handled. (Base class returns false)
	virtual bool isValid(string event_name);

	public:
	//constructor
	Manager();
	//destructor
	~Manager();

	//Register manager's interest in *object for event type
	//Return 0 for success, else -1
	int registerInterest(Object *p_o, string event_name);

	//Unregister manager's interest in event.
	//Return 0 for success, else -1
	int unregisterInterest(Object *p_o, string event_name);

	//Send event to all interested objects
	void onEvent(Event *p_event);

	// Starting up and shutting down managers
	virtual int startUp();
	virtual int shutDown();
	bool is_started; // true when started successfully
};

#endif


