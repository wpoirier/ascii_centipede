/*bullet.h
 *
 *projectile fired by player
 *destroys centipede nodes and mushrooms
 */

#ifndef BULLET_H
#define BULLET_H

#include "object.h"
#include "event.h"
#include "eventstep.h"
#include "player.h"


class Bullet: public Object {

//WHAT WE NEED:
//  collision with mushrooms and centipedes
//  conditions to remove bullet from object list when done

public:
	Bullet();
	Bullet(Position startpos, Player* player_pointer);
	~Bullet();

	Player* p_player;
	int eventHandler(Event* p_event);

};

#endif
