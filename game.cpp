/*game.cpp
 
 *********ASCII CENTIPEDE***********
 *********BY WILLIAM POIRIER********
 ************For IMGD 3000**********
 ************January 2014***********
 
 ----original game (C) 1981 Atari----
 ----by Edd Logg and Donna Bailey----
 */

//includes
#include "manager.h"
#include "logmanager.h"
#include "worldmanager.h"
#include "gamemanager.h"
#include "graphicsmanager.h"
#include "inputmanager.h"

#include "clock.h"
#include "object.h"
#include "objectlist.h"

//#include "event.h"
#include "eventstep.h"
#include "eventcollision.h"
#include "eventkeyboard.h"
#include "eventmouse.h"
#include "eventout.h"

#include "player.h"
#include "centnode.h"
#include "mushroom.h"
#include "gamecontrol.h"

//main function

int main() {

	//start up managers
	LogManager &log_manager = LogManager::getInstance();
	log_manager.startUp(true);
	log_manager.writeLog("Logmanager started. Iteration A%i", 1);

	WorldManager & world_manager = WorldManager::getInstance();
	log_manager.writeLog("Starting World Manager \n");
	world_manager.startUp();

	GameManager & game_manager = GameManager::getInstance();
	//game_manager.startUp();

	GraphicsManager & graphics_manager = GraphicsManager::getInstance();
	int gmstart = graphics_manager.startUp();
	log_manager.writeLog("graphics manager startup: %d", gmstart);


	log_manager.writeLog("y bound: %d",graphics_manager.getYBound());

	InputManager & input_manager = InputManager::getInstance();
	input_manager.startUp();


//***Player oject***/

	Player* player = new Player();
	
//**Set up game world via "gameControl" object
	new GameControl(player);

//***begin game loop  
	game_manager.run();

//**Remember to unregister objects from game and event list in shutdown**//

	//shut down managers at end of game loop
	graphics_manager.shutDown();
	input_manager.shutDown();
	world_manager.shutDown();
	game_manager.shutDown();
}
