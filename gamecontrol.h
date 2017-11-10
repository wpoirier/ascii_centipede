/**gamecontrol.h
 *
 *game object for controlling various game states based on world conditions
 *
 **/

#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include "object.h"
#include "player.h"

#define CENTIPEDES 5
#define CENT_MAX 20

#define MUSHROOMS 10
#define MUSH_MAX 50

#define START_POS Position(10,20)

class GameControl: public Object {

public:

	//constructors
	GameControl(Player* playerPtr);
	~GameControl();

	int phase; //phase (iteration) of the game
	int centcount; //number of centipede nodes on screen
	int mushcount; //number of mushrooms on screen
	int score; //game score during game
	int highscore; //highest score reached while game is running
	unsigned int seed; //seed for random mushroom/centipede generation

	static long int timer; //counter used in step event for timing purposes

	Player* p_player; //pointer to player object
	
	bool playing; //set to true to start the game

	//draw title screen
	void titleScreen();

	//show high score
	void showHighScore();

	//display user interface including lives and score
	void displayUI();

	//set value of playing to run the game
	//return 0 if successful  
	//NOTE: this does NOT end the game loop in game manager
	int setPlaying(bool set_play);

	//close this application
	//set gameManager.game_over to true
	void closeProgram();

	//draw game objects 
	void populateMushrooms();
	void populateCentipedes();

	//run an automaticly playing game demo
	void gameDemo();

	//Freeze game state
	//true if we want game paused
	bool freezeState();	
	
	//event handler for this object
	int eventHandler(Event *p_event);

	//draw method for this object
	void draw();

};

#endif


