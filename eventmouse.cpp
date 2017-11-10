//eventmouse.cpp

#include "eventmouse.h"

EventMouse::EventMouse() {
	this->event_type = MOUSE_EVENT;
}

EventMouse::~EventMouse() {}

//load mouse event's current action
void EventMouse::setMouseAction(enum MouseActionList new_mouse_action){}

//Get mouse event's action
enum MouseActionList EventMouse::getMouseAction(){}

//Set mouse event's x coordinate.
void EventMouse::setMouseX(int new_x){}

//Set mouse event's y coordinate
void EventMouse::setMouseY(int new_y){}

//Get mouse event's x coordinate.
int EventMouse::getMouseX(){}

//Get mouse event's y coordinate
int EventMouse::getMouseY(){}


