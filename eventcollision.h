//eventcollision.h

#ifndef EVENT_COLLISION_H
#define EVENT_COLLISION_H

#include "event.h"
#include "object.h"

#define COLLISION_EVENT "collision"

class EventCollision: public Event {

private:
	Position pos;	//where collision occured
	Object *p_obj1;	//Object moving causing collision
	Object *p_obj2;	//Object being collided with

public:
	//Create collision event at (0,0) with obj1 and obj2 NULL
	EventCollision();

	//Create collision between o1 and o2 and position p
	//Object o1 caused by collision moving into object o2
	EventCollision(Object *p_o1, Object *p_o2, Position p);

	//Return object that caused collision
	Object *getObject();
	//Set object that caused collision
	void setObject1(Object *p_new_o1);

	//Return object that was collided with
	Object *getObject2();

	//Set object that was collided with
	void setObject2(Object *p_new_o2);

	//Return position of the collision
	Position getPosition();

	//Set position of collision
	void setPosition(Position new_pos);

};

#endif
