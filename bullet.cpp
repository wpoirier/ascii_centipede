//bullet.cpp

#include "bullet.h"
#include "eventout.h"
#include "eventcollision.h"
#include "logmanager.h"
#include "worldmanager.h"

Bullet::Bullet() {
}

Bullet::Bullet(Position startpos, Player* player_pointer) {
	LogManager &lm = LogManager::getInstance();
	lm.writeLog("bullet created\n");

	p_player = player_pointer;
	
	type = "bullet";
	setPosition(startpos);
	setSprite('|');
	setYVelocity(-1.0);
	solidness = HARD;
}

Bullet::~Bullet() {

  	LogManager &lm = LogManager::getInstance();
	lm.writeLog("bullet destructor");

	
}

int Bullet::eventHandler(Event* p_event) {
	
	LogManager &lm = LogManager::getInstance();
	lm.writeLog("\n  Bullet event handler");
	lm.writeLog("Bullet position x:%d, y:%d", getPosition().getX(),getPosition().getY());


	if (p_event->getType() == COLLISION_EVENT) {
		//temp functionality
		WorldManager &wm = WorldManager::getInstance();		
		wm.markForDelete(this); //mark for delete		
		p_player->bulletcount--; //subtract player bullet count

		unregisterInterest(OUT_EVENT);
		unregisterInterest(COLLISION_EVENT);

	}

	if (p_event->getType() == OUT_EVENT) {
		WorldManager &wm = WorldManager::getInstance();		
		wm.markForDelete(this); //mark for delete
		p_player->bulletcount--; //subtract player bullet count
		
		unregisterInterest(OUT_EVENT);
		unregisterInterest(COLLISION_EVENT);
		lm.writeLog("bullet out event");
	}

	return 0;
}
