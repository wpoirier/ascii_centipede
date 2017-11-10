//player.h

#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"

class Player: public Object {

public:
	Player();
	~Player();

	int lives; //lives of player
	bool enable_input; //if true, keys may be pressed
	bool holding; //bool to detect space bar pressed or held
	int bulletcount;
	
	int invincible; //timer for how long player should be invincible
	bool damage; //set true to enable damage invincibility
	
	//When space is pressed, bullet fired
	void shoot();

	//Move player left or right
	void move(char);

	//draw lives count at top of screen 
	void displayLives();

	int eventHandler(Event* p_event);
	
	void draw();

};

#endif
