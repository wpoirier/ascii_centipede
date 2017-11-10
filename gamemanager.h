//gamemanager.h
#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "manager.h"

using namespace std;

class GameManager : public Manager {

private:
	GameManager(GameManager const&); //don't allow copy
	void operator =(GameManager const&); //don't allow assignment
	GameManager(); //private, because it's a singleton

protected:
	bool game_over; //when true, the game loop stops
	int frame_time; //target time per game loop, in milli-seconds

public:

	long int loop_iter; //loop iteration counter.

	~GameManager(); //destructor

	//get the singleton instance of the GameManager
	static GameManager &getInstance();

	int startUp(); //start up all game Manager services (only logmanager for now)
	int shutDown(); //clos game manager services and terminate program
	void setGameOver(bool);

	void run(); //run the game loop
	bool isValid(string event_name);
};

#endif
