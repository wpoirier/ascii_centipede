#ifndef EVENT_MOUSE_H
#define EVENT_MOUSE_H

/*eventmouse.h
 *
 * Event for mouse button press
 *
 */


#include "event.h"

#define MOUSE_EVENT "mouse"

enum MouseActionList {
	LEFT_BUTTON_CLICK,
	LEFT_BUTTON_DOUBLECLICK,
	RIGHT_BUTTON_CLICK,
	RIGHT_BUTTON_DOUBLECLICK,
	UNDEFINED
};

class EventMouse: public Event {

 private:
	enum MouseActionList mouse_action; //mouse action
	int mouse_x;			   //mouse x coordinate
	int mouse_y;			   //mouse y coordinate
	
 public:
	EventMouse();
	virtual ~EventMouse();
	
	//load mouse event's current action
	void setMouseAction(enum MouseActionList new_mouse_action);

	//Get mouse event's action
	enum MouseActionList getMouseAction();

	//Set mouse event's x coordinate.
	void setMouseX(int new_x);

	//Set mouse event's y coordinate
	void setMouseY(int new_y);

	//Get mouse event's x coordinate.
	int getMouseX();

	//Get mouse event's y coordinate
	int getMouseY();
	
};

#endif
