//gamecontrol.cpp

#include "gamecontrol.h"
#include "eventstep.h"
#include "eventkeyboard.h"
#include "graphicsmanager.h"
#include "inputmanager.h"
#include "gamemanager.h"
#include "worldmanager.h"
#include "objectlist.h"
#include "objectlistiterator.h"

#include "mushroom.h"
#include "centnode.h"

#include <stdlib.h>

GameControl::GameControl(Player* playerPtr){

	p_player = playerPtr;

	addToWorld();
	registerInterest(STEP_EVENT);
	registerInterest(KEYBOARD_EVENT);

	phase = 0;
	centcount = 0; 
	score = 0;
	highscore = 0; 
	playing = false;
	seed = 1;

}

GameControl::~GameControl(){}

int GameControl::eventHandler(Event *p_event)
{

	//if step event
	if (p_event->getType() == STEP_EVENT)
	{ 
		//timer for game delays
			//during this phase, set game input to false
		//if game not running, cycle through:
		if (!playing)
		{
		  	phase = 0;
			centcount = 0; 
			score = 0;
		}
		//if game running var set to true:
		if (playing)
		{
			//populate centipedes and mushrooms when there are no more 
			if (centcount <= 0)
			{
				phase++;
				populateCentipedes();
				populateMushrooms();
			}
			//control game based on player's lives
			if (p_player->lives > 0){
				p_player->enable_input = true;//enable player movement
				
				if (score >= highscore){
				
				    highscore = score;
				}
			}
			else if (p_player->lives <= 0){
				p_player->enable_input = false;
				playing = false;
				p_player->setPosition(Position(-1, -1));
				WorldManager &wm = WorldManager::getInstance();
				ObjectList objlist = wm.getAllGameObjects();
				ObjectListIterator *o_i = new ObjectListIterator(&objlist);
				
				while(!o_i->isDone()){
				  if(o_i->currentItem() != this && o_i->currentItem() != p_player){
				    wm.markForDelete(o_i->currentItem());				   
				  }
				  o_i->next();
				    
				}
			}
		}
	}
	
	//if input event
	if (p_event->getType() == KEYBOARD_EVENT)
	{
		//static cast p_event to p_inputevent
		EventKeyboard *p_kbevent = static_cast<EventKeyboard *>(p_event);
		int key = p_kbevent->getKey();

		//switch statement for KEY being pressed
		if(!playing)
		{	
			switch(key)			
			{	  
				case 'p':
					playing = true;
					phase = 1;
					populateMushrooms();
					populateCentipedes();
					p_player->lives = 3; //player starts with 3 lives
					p_player->setPosition(START_POS);
					//start game
					break;
				case 'q':
					closeProgram(); //quit game
					break;
				//case 1, 2, or 3
					//seed random number generator (game mode)
			}
		}
	}
			
}

void GameControl::titleScreen(){
	GraphicsManager &graphics_manager = GraphicsManager::getInstance();
	int max_x = graphics_manager.getXBound();
	int max_y = graphics_manager.getYBound();
	
	mvprintw( max_y - 4, 5, "High Score: %d", highscore);
	
	graphics_manager.drawString( Position(max_x/2, max_y/2 - 4), "ASCII CENTIPEDES", CENTER_JUSTIFIED);
	graphics_manager.drawString( Position(max_x/2, max_y/2), "by William Poirier", CENTER_JUSTIFIED);
	graphics_manager.drawString( Position(max_x/2, max_y/2 + 1), "2013, 2014", CENTER_JUSTIFIED);
	graphics_manager.drawString( Position(max_x/2, max_y/2 + 3), "original game (c) 1981 Atari \n by by Edd Logg and Donna Bailey", 		CENTER_JUSTIFIED);
	graphics_manager.drawString( Position(max_x/2, max_y/2 + 6), "Press P to Start", CENTER_JUSTIFIED);

	graphics_manager.drawString( Position(max_x/2, max_y/2 + 8), "Shoot with SPACE, move with WASD", LEFT_JUSTIFIED);
	graphics_manager.drawString( Position(max_x/2, max_y/2 + 9), "Hit Q to quit", LEFT_JUSTIFIED);

}

void GameControl::showHighScore(){
	GraphicsManager &graphics_manager = GraphicsManager::getInstance();
	int max_x = graphics_manager.getXBound();
	int max_y = graphics_manager.getYBound();
	mvprintw( max_y - 4, 5, "High Score: %d", highscore);
}

void GameControl::displayUI(){
	GraphicsManager &graphics_manager = GraphicsManager::getInstance();
	int max_x = graphics_manager.getXBound();

	mvwprintw( graphics_manager.buffer, 1, 1, "Score: %d", score);	
	mvwprintw( graphics_manager.buffer, 2, 1, "Highs: %d", highscore);	
	mvwprintw( graphics_manager.buffer, 3, 1, "Lives: %d", p_player->lives);

	mvwprintw( graphics_manager.buffer, 1, max_x/2, "Centi: %d", centcount);
	mvwprintw( graphics_manager.buffer, 2, max_x/2, "Phase: %d", phase);
}

void GameControl::closeProgram(){
	GraphicsManager &graphics_manager = GraphicsManager::getInstance();
	graphics_manager.clear();
	int max_x = graphics_manager.getXBound();
	int max_y = graphics_manager.getYBound();
	graphics_manager.drawString( Position(max_x/2, max_y/2), "Goodbye! :)", LEFT_JUSTIFIED);
	GameManager &game_manager = GameManager::getInstance();
	game_manager.setGameOver(true);
	//pause for a moment
	//initiate manager shutdown process (gm.game_over = true)
}

void GameControl::populateMushrooms(){

	GraphicsManager &gm = GraphicsManager::getInstance();
	srand(seed + phase);

	for (int i = 0; i <= MUSHROOMS; i++)
	{
		int x = rand() % gm.getXBound() - 1;
		int y = (rand() % 15) + 4;//1 + (gm.getYBound() - 1 );

		if (mushcount <= MUSH_MAX){
			new Mushroom(x,y,this);
			mushcount++;
		}
		
	}
}

void GameControl::populateCentipedes(){

	GraphicsManager &gm = GraphicsManager::getInstance();
	srand(seed + phase %5);

	for (int i = 0; i <= CENTIPEDES + phase; i++)
	{
		int x = rand() % gm.getXBound();
		int y = (rand() % 10) + 4;//1 + (gm.getYBound() - 1 );

		if (centcount <= CENT_MAX){
			new Centnode(x,y,this);
			centcount++;
		}
	}
}

void GameControl::draw(){
	if (!playing){
	  //showHighScore();
	  titleScreen();
	}

	if (playing){
		displayUI();
	}

}
