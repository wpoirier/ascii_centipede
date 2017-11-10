//mushroom.cpp

#include "mushroom.h"
#include "eventcollision.h"
#include "logmanager.h"
#include "worldmanager.h"
#include "graphicsmanager.h"

Mushroom::Mushroom(){}

//constructor
Mushroom::Mushroom(int x, int y, GameControl* gcp) {
	setXVelocity(0);
	setYVelocity(0);
	health = 3; //initial health is 3
	setSprite('M');
	type = "mushroom";

	pos = Position(x,y);
	
	addToWorld();
	registerInterest(COLLISION_EVENT);

	gc_ptr = gcp;
}

Mushroom::~Mushroom() {}

int Mushroom::eventHandler(Event *p_event) {
	/**in some sort of event, either a step event or custom event,
	 it will be alerted when the health of this object has changed.
	 Run these conditions (through the changeSprite function);
	 -if health == 3, sprite is 'M'
	 -if health == 2, sprite is 'N'
	 -if health == 1, sprite is 'n'
	 *if health <= 0, mark for delete
	 **/

	WorldManager &wm = WorldManager::getInstance();
	
	if (health <= 0){
		wm.markForDelete(this);
		gc_ptr->mushcount--;
		gc_ptr->score++;
		unregisterInterest(COLLISION_EVENT); 
	}

	if (p_event->getType() == COLLISION_EVENT)
	{
		EventCollision *p_cEvent = static_cast<EventCollision *>(p_event);
		if (p_cEvent->getObject()->getType() == "bullet"){
		  health--;
		  changeSprite(health);
		}
	}

	//In a collision event, decrease health by one
	return 0;
}

//Change sprite based on int h, representing "health"
void Mushroom::changeSprite(int h) {
	switch (h) {
	case 3:
		setSprite('M');
		break;
	case 2:
		setSprite('m');
		break;
	case 1:
		setSprite('_');
		break;
	}
}

void Mushroom::draw(){

  GraphicsManager &gm = GraphicsManager::getInstance();
  
  //change color depending on game phase
  switch (gc_ptr->phase)
  {
    case 1:
      gm.writeChar(pos, sprite, COLOR_RED);
      break;
    case 2:
      gm.writeChar(pos, sprite, COLOR_GREEN);
      break;
    case 3:
      gm.writeChar(pos, sprite, COLOR_MAGENTA);
      break;
    default:
      gm.writeChar(pos, sprite, COLOR_CYAN);
  }
}