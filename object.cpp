#include "object.h"
#include "worldmanager.h"
#include "graphicsmanager.h"

#include "inputmanager.h"	
#include "gamemanager.h"
//#include "objectlistiterator.h"
#include "logmanager.h"

//#include "event.h"
#include "eventstep.h"
#include "eventcollision.h"
#include "eventkeyboard.h"
#include "eventmouse.h"
#include "eventout.h"

#include <math.h>

//default constructor (no arguments in method)
Object::Object() {
//	LogManager &lm = LogManager::getInstance();
//	lm.writeLog("top of object constructor");
// WorldManager &wm = WorldManager::getInstance();//get instance of worldmanager
	//GraphicsManager &gm = GraphicsManager::getInstance();

	Position newPos;
	pos = newPos;
	type = "object"; //set default type  
	x_velocity = 0;
	y_velocity = 0;
	x_vcountdown = 0;
	y_vcountdown = 0;
	sprite = '.';
	solidness = SPECTRAL;
	event_count = 0;

	//wm.insertGameObject(this);//add object to wm game object list:
	//gm.writeChar(pos, sprite);
}

Object::~Object() {
	WorldManager &wm = WorldManager::getInstance();//get instance of worldmanager
	wm.removeGameObject(this);//remove object from list

	for (int i = 0; i < event_count; i++) {
		unregisterInterest(event_name[i]);
	}	
}

int Object::addToWorld() {
	WorldManager &wm = WorldManager::getInstance();//get instance of worldmanager
	wm.insertGameObject(this);

	return 0;
}

void Object::setType(string new_type) {
	type = new_type;
}

string Object::getType() {
	return type;
}

//true if HARD or SOFT, false if SPECTRAL
bool Object::isSolid() {
	if (solidness == HARD || SOFT)
		return true;
	else
		return false;
}

//return object solidness
int Object::getSolidness() {
	return solidness;
}

int Object::setSolidness(Solidness new_solid) {
	solidness = new_solid;
}

void Object::setSprite(char sp) {
	sprite = sp;
}

char Object::getSprite() {
	return sprite;
}

void Object::setPosition(Position new_pos) {
	pos = new_pos;
}

Position Object::getPosition() {
	return pos;
}

double Object::getXVelocity() {
	return x_velocity;
}

void Object::setXVelocity(double xv) {
	x_velocity = xv;
	x_vcountdown = 1;
}

double Object::getYVelocity() {
	return y_velocity;
}

void Object::setYVelocity(double yv) {
	y_velocity = yv;
	y_vcountdown = 1;
}

int Object::getXVelocityStep() {
	double spaces;

	if (x_velocity == 0)
		return 0; //velocity is zero, no need to move

	x_vcountdown = x_vcountdown - fabs(x_velocity);
	if (x_vcountdown > 0)
		return 0; //not yet time to move  

	//Countdown now 0, so figure out how far to move
	spaces = floor(1.0 - x_vcountdown);
	x_vcountdown = 1 + fmod(x_vcountdown, 1);

	//return number of spaces to move
	if (x_velocity > 0)
		return (int) spaces;
	else
		return -1 * (int) spaces;

}

int Object::getYVelocityStep() {

	double spaces;

	if (y_velocity == 0)
		return 0; //velocity is zero, no need to move

	y_vcountdown = y_vcountdown - fabs(y_velocity);
	if (y_vcountdown > 0)
		return 0; //not yet time to move  

	//Countdown now 0, so figure out how far to move
	spaces = floor(1.0 - y_vcountdown);
	y_vcountdown = 1 + fmod(y_vcountdown, 1);

	//return number of spaces to move
	if (y_velocity > 0)
		return (int) spaces;
	else
		return -1 * (int) spaces;

}

int Object::eventHandler(Event *p_event) {
	return 1;
}

int Object::registerInterest(string event) {
	GameManager &gm = GameManager::getInstance();
	WorldManager &wm = WorldManager::getInstance();
	InputManager &im = InputManager::getInstance();
	
	if (event_count == MAX_EVENTS) {
		return -1;
	}
	
	if (event == COLLISION_EVENT) {
		if(wm.registerInterest(this, event) != 0) {
			return -1;
		}
	} 
	
	else if (event == KEYBOARD_EVENT) {
		if(im.registerInterest(this, event) != 0) {
			return -1;
		}
	}

	else if (event == MOUSE_EVENT) {
		if(im.registerInterest(this, event) != 0) {
			return -1;
		}
	}
	
	else if (event == OUT_EVENT) {
		if(wm.registerInterest(this, event) != 0) {
			return -1;
		}
	}

	else if (event == STEP_EVENT) { 
		if(gm.registerInterest(this, event) != 0) {
			return -1;
		}
	}

	else if(wm.registerInterest(this, event) != 0) {
		return -1;
	}

	// Keep track of added event
	event_name[event_count] = event;
	event_count++;

	return 0; // Sucess!	
	
}

int Object::unregisterInterest(string event) { 

	LogManager &lm = LogManager::getInstance();
	lm.writeLog("Object: unregister interest");

	int found = -1;
	
	for (int i = 0; i < event_count; i++) {
		if (event_name[i] == event) {
			found = i; // remember where the event was found
			break;
		}
	}
	
	if (found == -1) return -1;
	
	GameManager &gm = GameManager::getInstance();
	WorldManager &wm = WorldManager::getInstance();
	
	if (event_count == MAX_EVENTS) {
		return -1;
	}
	
	if (event == COLLISION_EVENT) {
		if(wm.unregisterInterest(this, event) != 0) {
			return -1;
		}
	} 
	
	else if (event == KEYBOARD_EVENT) {
		if(gm.unregisterInterest(this, event) != 0) {
			return -1;
		}
	}

	else if (event == MOUSE_EVENT) {
		if(wm.unregisterInterest(this, event) != 0) {
			return -1;
		}
	}
	
	else if (event == OUT_EVENT) {
		if(wm.unregisterInterest(this, event) != 0) {
			return -1;
		}
	}

	else if (event == STEP_EVENT) { 
		if(wm.unregisterInterest(this, event) != 0) {
			return -1;
		}
	}

	else if(wm.unregisterInterest(this, event) != 0) {
		return -1;
	}

	// Index where event was found is saved in var found
	for (int j = found; j < event_count - 1; j++) {
		event_name[j] = event_name[j + 1];
		//event_name[j + 1] = NULL;
	}
	
	event_count--;
	return 0;	
	
};


void Object::draw(){
	
}
