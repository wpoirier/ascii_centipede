/* eventout.h
 *
 * event for objects exiting screen boundry
 *
 */

#include "event.h"

#define OUT_EVENT "out"

class EventOut: public Event {
public:
	EventOut();
	Event out_event;
};
