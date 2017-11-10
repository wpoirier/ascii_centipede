#ifndef EVENT_KEYBOARD_H
#define EVENT_KEYBOARD_H

#include "event.h"
#include "object.h"

#define KEYBOARD_EVENT "keyboard"

class EventKeyboard: public Event {

private:
	char key; //key value to store

public:
	EventKeyboard();

	//set key in event
	void setKey(char new_key);

	//return value of "key"
	char getKey();

};

#endif

