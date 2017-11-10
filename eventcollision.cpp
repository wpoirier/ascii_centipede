//eventcollision.cpp

#include "eventcollision.h"
#include "logmanager.h"

EventCollision::EventCollision() {
	p_obj1 = NULL;
	p_obj2 = NULL;
	pos = Position(0, 0);
	this->event_type = COLLISION_EVENT;
}

EventCollision::EventCollision(Object *p_o1, Object *p_o2, Position p) {
	p_obj1 = p_o1;
	p_obj2 = p_o2;
	pos = p;
	event_type = COLLISION_EVENT;
}

//Return object that caused collision
Object *EventCollision::getObject() {
	return p_obj1;
}

//Set object that caused collision
void EventCollision::setObject1(Object *p_new_o1) {
	p_obj1 = p_new_o1;
}

//Return object that was collided with
Object *EventCollision::getObject2() {
	return p_obj2;
}

//Set object that was collided with
void EventCollision::setObject2(Object *p_new_o2) {
	p_obj2 = p_new_o2;
}

//Return position of the collision
Position EventCollision::getPosition() {
	return pos;
}

//Set position of collision
void EventCollision::setPosition(Position new_pos) {
	pos = new_pos;
}
