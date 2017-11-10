//eventstep.h
//a step event generated once per loop

#ifndef __EVENT_STEP_H__
#define __EVENT_STEP_H__

#define STEP_EVENT "step"

#include "event.h"

class EventStep: public Event {
public:
	EventStep(); //constructor
	Event step_event;
};

#endif
