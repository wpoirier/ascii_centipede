//***Dragonfly Test Cases part 1:***
//****William Poirier****
//****November 2013******

#include <stdio.h>
#include <string>

#include "manager.h"
#include "logmanager.h"
#include "worldmanager.h"
#include "gamemanager.h"
#include "graphicsmanager.h"
#include "inputmanager.h"

#include "clock.h"
#include "object.h"
#include "objectlist.h"

#include "event.h"
#include "eventstep.h"
/*#include "eventkeyboard.h"
 #include "eventmouse.h"
 #include "eventout.h"
 #include "eventcollision.h"
 */
//Game Initializations
//Main Function
int main() {

	// Manager::Manager();

	//start up managers
	LogManager &log_manager = LogManager::getInstance();
	log_manager.startUp(true);
	log_manager.writeLog("Logmanager started. Iteration A%i", 1);

	WorldManager & world_manager = WorldManager::getInstance();
	log_manager.writeLog("Starting World Manager \n");
	world_manager.startUp();

	GameManager & game_manager = GameManager::getInstance();
	// game_manager.startUp();

	GraphicsManager & graphics_manager = GraphicsManager::getInstance();
	graphics_manager.startUp();

	//testing graphics manager
	Position posGraphic(10, 10);
	graphics_manager.writeChar(posGraphic, '#');

	//create some objects:
	Object* foo = new Object();
	Object* bar = new Object();
	Object* snaf = new Object();

	foo->setSprite(125);
	graphics_manager.writeChar(foo->getPosition(), foo->getSprite());
	foo->setXVelocity(1.0);

	Position posBar(7, 14);
	bar->setPosition(posBar);

	//insert objects to list
	world_manager.insertGameObject(foo);
	log_manager.writeLog("inserted foo\n");
	world_manager.insertGameObject(bar);
	log_manager.writeLog("inserted bar \n");
	world_manager.insertGameObject(snaf);
	log_manager.writeLog("inserted snaf \n");

	//Run Game Loop
	game_manager.run();

	//Shut down managers at end of game loop
	log_manager.writeLog("shutting down managers");

	graphics_manager.shutDown();

}

