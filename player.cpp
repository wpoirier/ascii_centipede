//player.cpp

#include "player.h"
#include "bullet.h"
#include "eventkeyboard.h"
#include "eventstep.h"
#include "eventout.h"
#include "eventmouse.h"
#include "eventcollision.h"
#include "worldmanager.h"
#include "graphicsmanager.h"
#include "logmanager.h"

//constructor
Player::Player() {
	setSprite('T');
	setPosition(Position(-1, -1));
	lives = 0;
	enable_input = false;
	holding = false;
	
	solidness = SOFT;
	
	invincible = 5;
	damage = false;
	
	registerInterest(KEYBOARD_EVENT);
	registerInterest(OUT_EVENT);
	registerInterest(STEP_EVENT);
	registerInterest(COLLISION_EVENT);
	addToWorld();
}

//Destructor
Player::~Player() {
	unregisterInterest(KEYBOARD_EVENT);
	unregisterInterest(OUT_EVENT);
	unregisterInterest(STEP_EVENT);
	unregisterInterest(COLLISION_EVENT);
}

//event handler
int Player::eventHandler(Event* p_event) {

	LogManager &lm = LogManager::getInstance();
	lm.writeLog("\n  Player event handler");

	std::string str = p_event->getType();
	const char * c = str.c_str();
	lm.writeLog("  -- p_event type: %s", c);

	if (p_event->getType() == STEP_EVENT) {

		if (lives <= 0) enable_input = false;
		else enable_input = true;
		//if (holding) holding = false;

		if (damage){
		  invincible--;
		  if (invincible <=0) {damage = false; invincible = 5;}
		}
		
		lm.writeLog("\n BAHHHHHHHHH!!!!!!!! \n");
		lm.writeLog("da playa's position x:%d, y:%d", getPosition().getX(),getPosition().getY());
	}

	if (p_event->getType() == KEYBOARD_EVENT && enable_input) {

		lm.writeLog("\n Player Event Handler: keyboard");

		EventKeyboard *p_kbevent = static_cast<EventKeyboard *>(p_event);

		lm.writeLog("value of p_kbevent: %c", p_kbevent->getKey());
		move(p_kbevent->getKey());
	}
	
	if (p_event->getType() == MOUSE_EVENT){
		setYVelocity(-1);
	}
	
	if (p_event->getType() == OUT_EVENT) {
		lm.writeLog("object reached boundry");
		setXVelocity(0);
	}
	
	if (p_event->getType() == COLLISION_EVENT){
		EventCollision *p_cEvent = static_cast<EventCollision *>(p_event);
		//if the collision was with a mushroom
		if (p_cEvent->getObject()->getType() == "centipede" && !damage)
		{
						
			lives--; //subtract lives
			damage = true;			
		}
	}


	return 0;
}
  
//movement
void Player::move(char key) {

	int x = getPosition().getX(); 
	int y = getPosition().getY();

	GraphicsManager &gm = GraphicsManager::getInstance();

	if (key == 'a' && x > 2)
		setPosition( Position(x - 1, y) ); //move 1 space left
	else if (key == 'd'&& x < gm.getXBound() - 2)
		setPosition( Position(x + 1, y ) ); //move one space right
	else if (key == 'w' && y >= gm.getYBound() - 4 )
		setPosition( Position(x, y - 1) ); //move up
	else if (key == 's'&& y < gm.getYBound() - 2)
		setPosition( Position(x, y + 1) ); //move down

	if (key == 32 && !holding) { //if space bar
		holding = true;
		//Create a new bullet one space above player
		int x_o = this->getPosition().getX();
		int y_o = this->getPosition().getY();
		Position player_offset(x_o, y_o);

		if (bulletcount < 3){
			Bullet *b = new Bullet(player_offset, this); //create bullet        
			b->registerInterest(OUT_EVENT);
			b->registerInterest(COLLISION_EVENT);
			//b->registerInterest(STEP_EVENT);
			b->addToWorld();
			bulletcount++;
		}
	}
	else holding = false;
}

void Player::draw(){
	GraphicsManager &gm = GraphicsManager::getInstance();
	if (damage) gm.writeChar(pos, '*');
}