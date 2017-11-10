/**centnode.h
 *
 *Enemy centipede character.
 Follows chains of more centipede nodes.
 *
 *The front is denoted by a "leader" node.
 *  
 *When a leader touches a mushroom or the screen edge,
 it will shift down a space and change horizontal direction.
 Nodes behind leader will follow 
 *
 *If a node is destroyed in the middle, the node previous to 
 the destroyed node in the relative velocity becomes a new leader. 
 The chain will split off and follow the new leader on a new path.
 *
 *nodes change into mushrooms when shot
 *
 *Character used for sprite: 'o'
 *
 **/

#ifndef CENTINODE_H
#define CENTINODE_H

#include "object.h"
#include "event.h"
#include "gamecontrol.h"

class Centnode: public Object {

public:

	float v_base; //base horizontal velocity 
	float v_scale; //scale base velocity up as game time goes on

	GameControl* gc_ptr; //pointer to the game control object

	//constructor and destructor
	Centnode();
	Centnode(int, int, GameControl*);
	~Centnode();

	//event handler for centnode object
	int eventHandler(Event* p_event);

	//follow leader node in his direction
	void followLeader();

	//signal for collision with player
	int hitPlayer();

	//
	int changeDir(int direction);

	//shift down space and change direction when hit mushroom or world boundry.
	void shiftDown();
	
	void draw();
};

#endif
