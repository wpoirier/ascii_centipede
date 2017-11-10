/*mushroom.h
 *
 *Mushroom character that causes centipede chain to shift down 
 *Can be destroyed for points by player
 *
 */

#ifndef MUSHROOM_H
#define MUSHROOM_H

#include "object.h"
#include "gamecontrol.h"

class Mushroom: public Object {

public:

	int health; //hit points
	GameControl* gc_ptr; //pointer to the game control object

	//constructor and destructor
	Mushroom();
	Mushroom(int x, int y, GameControl*);
	~Mushroom();

	//change "sprite" char depending on health
	void changeSprite(int h);
	int eventHandler(Event *p_event);
	
	void draw();
};

#endif 
