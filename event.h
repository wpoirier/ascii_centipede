//event.h

#ifndef __EVENT_H__
#define __EVENT_H__

#define MAX_EVENTS 100

#include <string>

using namespace std;

class Event {

public:
	Event(); //constructor
	virtual ~Event(); //destructor

	void setType(string new_type);
	string event_type;

	string getType(); //get event type
};

#endif
