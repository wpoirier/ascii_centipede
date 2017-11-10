//worldmanager.h

#ifndef _WORLD_MANAGER_H_
#define _WORLD_MANAGER_H_

#include "manager.h"
#include "objectlist.h"
#include "event.h"

class WorldManager : public Manager {

private:
	//int obj_id;                          ///< Next object id to assign.
	WorldManager(WorldManager const&);  ///< Don't allow copy.
	void operator=(WorldManager const&); ///< Don't allow assignment.
	WorldManager();

public:
	ObjectList gameList;
	ObjectList deleteList;

	// public:
	~WorldManager();

	// Get the one and only instance of the WorldManager.
	static WorldManager &getInstance();

	/// Indicate object is to be deleted at end of current game loop.
	/// Return 0 if ok, else -1.
	int markForDelete(Object *p_o);

	//update game world
	//Delete objects "marked for delete"
	void update();

	// Return a list of all GameObjects in world.
	// Return NULL if list is empty.
	ObjectList getAllGameObjects(void);

	// Add GameObject to world.
	// Return 0 if ok, else -1.
	int insertGameObject(Object *p_o);

	// Remove GameObject from world.
	// Return 0 if ok, else -1.
	int removeGameObject(Object *p_o);

	//draw all game objects
	void draw();

	//Return true if two positions are the same
	bool positionsIntersect(Position p1, Position p2);

	//Return List of Objects collided with at position "where"
	//Collisions only with solid objects
	//does not consider if pointer to object (p_o) is solid or not
	ObjectList isCollision(Object *p_o, Position where);

	//Move Object
	//if no collision with solid, allow move. Else, don't move
	//Return 0 to allow move, -1 (to not) if collision with solid
	int moveObject(Object *p_o, Position where);

	//start up the game world and initialize everything to zero
	//return 0 for sucess
	int startUp();
	//shut down game world
	int shutDown();

	bool isValid(string event_name);
};

#endif
