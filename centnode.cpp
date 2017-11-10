//centnode.cpp

#include "centnode.h"
#include "eventstep.h"
#include "eventcollision.h"
#include "eventout.h"
#include "graphicsmanager.h"
#include "logmanager.h"
#include "worldmanager.h"

//constructor
Centnode::Centnode(int x, int y, GameControl* gcp) {

	registerInterest(STEP_EVENT);
	registerInterest(COLLISION_EVENT);
	registerInterest(OUT_EVENT);
	addToWorld();

	setType("centipede");
	setSprite('O');

	pos = Position(x,y);
	solidness = SOFT;

	gc_ptr = gcp;
	setXVelocity( (double) gcp->phase * 0.25 );

}

//destructor
Centnode::~Centnode() {}

//event handler
int Centnode::eventHandler(Event* p_event)
{
	if (p_event->getType() == STEP_EVENT)
	{
		GraphicsManager &gm = GraphicsManager::getInstance();//get graphics manager instance		
		//get centnode's x and y position
		int p_x = getPosition().getX();
		int p_y = getPosition().getY();

		//if reached right edge of screen (but not outside)
		if (p_x > gm.getXBound() - 5){
			setPosition( Position(p_x - 1, p_y + 1));//go down one space 
			setXVelocity(-0.25 * (double) gc_ptr->phase );//reverse direction
		}
		else if (p_x <= 1){
			setPosition( Position(p_x + 1, p_y + 1));//go down one space 
			setXVelocity(0.25 * (double) gc_ptr->phase );//reverse direction
		}
			
	}
	
	LogManager &lm = LogManager::getInstance();
	lm.writeLog("Centnode: event type ==%s", p_event->getType().c_str());
	if (p_event->getType() == COLLISION_EVENT)
	{
		EventCollision *p_cEvent = static_cast<EventCollision *>(p_event);

		//get collision event parameters
		//Object* o_cent = p_event->getObject();
		//Object* o_collided = p_event->getObject2();	
		lm.writeLog("Centnode: event type was indeed collision");
		//if the collision was with a mushroom
		if (p_cEvent->getObject2()->getType() == "mushroom")
		{
			setPosition( Position (getPosition().getX(), getPosition().getY() + 1) ); //move down one space			 
		}

		if (p_cEvent->getObject2()->getType() == "centipede")
		{
			setXVelocity( getXVelocity() * -1.0 );//reverse direction
		}
		
		if (p_cEvent->getObject2()->getType() == "bullet"  || p_cEvent->getObject()->getType() == "bullet")
		{
			WorldManager &wm = WorldManager::getInstance();
			gc_ptr->centcount--; //decrease count of centipede nodes in world		
			gc_ptr->score += 3; //increase score
			wm.markForDelete(this);
			unregisterInterest(STEP_EVENT);
			unregisterInterest(COLLISION_EVENT);
			unregisterInterest(OUT_EVENT);

			//if the number of centnodes is zero, next phase
		}
		
		//if the collision was with the player
			//kill player 
	}

	//if outside world
	if (p_event->getType() == OUT_EVENT){
		WorldManager &wm = WorldManager::getInstance();
		gc_ptr->centcount--; //decrease count of centipede nodes in world		
		wm.markForDelete(this);
		unregisterInterest(STEP_EVENT);
		unregisterInterest(COLLISION_EVENT);
		unregisterInterest(OUT_EVENT);

		lm.writeLog("Centnode: outside world");
	}
		
}

int Centnode::changeDir(int direction){
	//reverse x velocity
}

void Centnode::draw(){
	GraphicsManager &gm = GraphicsManager::getInstance();
  
	//change color depending on game phase
	switch (gc_ptr->phase)
	{
	  case 1:
	    gm.writeChar(pos, sprite, COLOR_GREEN);
	    break;
	  case 2:
	    gm.writeChar(pos, sprite, COLOR_YELLOW);
	    break;
	  case 3:
	    gm.writeChar(pos, sprite, COLOR_RED);
	    break;
	
	  default:
	    gm.writeChar(pos, sprite, COLOR_WHITE);
	}
}
