//event.cpp

#include "event.h"

Event::Event() {
}
Event::~Event() {
}

void Event::setType(string new_type) {
	event_type = new_type;
}
string Event::getType() {
	return event_type;
}
