//gamemanager.cpp

#include "worldmanager.h"
#include "gamemanager.h"
#include "worldmanager.h"
#include "graphicsmanager.h"
#include "inputmanager.h"
#include "logmanager.h"
#include "clock.h"
#include "objectlistiterator.h"

#include <stdlib.h>
#include <unistd.h>

#include "eventstep.h"
#include "eventcollision.h"
#include "eventkeyboard.h"
#include "eventmouse.h"
#include "eventout.h"

GameManager::GameManager(){ //:Manager(){
//  loop_iter = 0;
}
GameManager::~GameManager(){}

//get singleton instance of GameManager
GameManager & GameManager::getInstance(){  
  static GameManager single_instance;
  return single_instance;
}

//run the game loop
void GameManager::run() {
 
  LogManager &lm = LogManager::getInstance();
  loop_iter = 0;

  Clock * engine_clock = new Clock;
  long int elapsed_time;
 
  WorldManager &world_manager = WorldManager::getInstance();
  InputManager &input_manager = InputManager::getInstance();
  GraphicsManager &graphics_manager = GraphicsManager::getInstance();

  //list of game objects
  const ObjectList* l_p = &world_manager.gameList;
  ObjectListIterator* p_li = new ObjectListIterator(l_p);
  

  while (!game_over){

    lm.writeLog("\n*---TOP OF GAME LOOP---* \n   loop iteration == %d\n", loop_iter);
    //initial time at begining of loop
    engine_clock->initialTime();
        //write log manager loop iteration and initial time
	lm.writeLog("initial time: %d", engine_clock->init_t.tv_usec);

	//get key/mouse input
	input_manager.getKey();

	//run step event
	EventStep s;
	onEvent(&s);
	
	//clear current buffer 
	graphics_manager.clear();

    //update world
	world_manager.update();
	
	//draw game object characters
	world_manager.draw();
	graphics_manager.swapBuffers();

	//Timing the refresh rate
	elapsed_time = engine_clock->calcDelta();//time it took for one loop iteration
	lm.writeLog("elapsed time: %d \n sleeptime: %d", elapsed_time, 
				TARGET_TIME - elapsed_time);

	if (elapsed_time <= TARGET_TIME)
		usleep(32000 - elapsed_time);

	//usleep(3200);
 
	loop_iter++; //keep track of looper iteration

	lm.writeLog("*** Bottom of GAMEMANAGER GAME LOOP ***\n\n");
   } 

}

//To be implemented in 2B. LogManager startUp does work, but is currently in the main function.

int GameManager::startUp(){
//  LogManager::startUp();
	is_started = true;
	return 0;
}

int GameManager::shutDown(){
//  LogManager::shutDown();
	exit (1);
	return 0;
}

void GameManager::setGameOver(bool value){
	game_over = value;
}

bool GameManager::isValid(string event_name) {
	// Takes a step event
	if (event_name == STEP_EVENT) {
		return true;
	}
	else return false;
}

