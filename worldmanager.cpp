//worldmanager.cpp

#include "worldmanager.h"
#include "graphicsmanager.h"
#include "event.h"
#include "eventcollision.h"
#include "eventout.h"
#include "object.h"
#include "objectlistiterator.h"
#include "objectlist.h"
#include "logmanager.h"
//#include <iostream>

using namespace std;

WorldManager::WorldManager() {
//  LogManager &lm = LogManager::getInstance();
//  lm.writeLog("****WorldManager Constructor***\n");
}
WorldManager::~WorldManager() {}

int WorldManager::startUp(){
//  LogManager::startUp();
	is_started = true;
	return 0;
}

int WorldManager::shutDown(){
//  LogManager::shutDown();
	return 0;
}



WorldManager & WorldManager::getInstance() {
//	LogManager &lm = LogManager::getInstance();
//	lm.writeLog("1.top of worldmanager.getinstance\n");
	static WorldManager single_instance;
//	lm.writeLog("2. static WorldManager single_instance declared\n");
	return single_instance;
}


//Insert object into main game list
int WorldManager::insertGameObject(Object *p_o) {
	gameList.insert(p_o);
	return 0;
}

int WorldManager::markForDelete(Object *p_o) {
	//create a new objectlist iterator
	//if object is not in delete list already
	deleteList.insert(p_o);
	return 0;
}

int WorldManager::removeGameObject(Object *p_o) {
	//iterate through delete list
	//if object is in delete list then:
	gameList.remove(p_o); //remove object from game list
	return 0;
}

ObjectList WorldManager::getAllGameObjects(void) {
	return gameList;
}

void WorldManager::draw(){

	GraphicsManager &gm = GraphicsManager::getInstance();
	
	const ObjectList* l_p = &gameList;
	ObjectListIterator* i = new ObjectListIterator(l_p);
	
	while (!i->isDone()) {

		Position objpos = i->currentItem()->getPosition();
		char objch = i->currentItem()->getSprite();

		//write character
		if (((objpos.getX() < gm.getXBound() - 1) && (objpos.getX() > 1))
			&& ((objpos.getY() < gm.getYBound() - 1) && (objpos.getY() > 1))) 
		{
				gm.writeChar(objpos, objch); //draw object's character
		}

		i->currentItem()->draw(); //called for programmers wishing to override 
		i->next();
	}

}

bool WorldManager::positionsIntersect(Position p1, Position p2) {
	if (p1.getX() == p2.getX() && p1.getY() == p2.getY())
		return true;
	return false;
}

ObjectList WorldManager::isCollision(Object *p_o, Position where) {

	ObjectList collisionList; //make an empty list

	//iterate through all objects:

	const ObjectList* l_p = &gameList;
	ObjectListIterator* i = new ObjectListIterator(l_p);

	while (!i->isDone()) {

		Object* p_temp_o = i->currentItem();

		if (p_temp_o != p_o) { //do not consider self

			if (positionsIntersect(p_temp_o->getPosition(), where)
					&& p_temp_o->isSolid()) { //if at same location AND solid
				collisionList.insert(p_temp_o); //add p_temp_o to collision list
			}
		}
		i->next();
	}
	return collisionList;
}

//move objects depending on collision state
int WorldManager::moveObject(Object *p_o, Position where) {
	bool do_move;
	if (p_o->isSolid()) {
		//list of objects to move
		ObjectList list = isCollision(p_o, where);

		//if list is not empty {
		const ObjectList* l_p = &list;
		ObjectListIterator *i = new ObjectListIterator(l_p);

		while (!i->isDone()) {
			Object * p_temp_o = i->currentItem();

			//create collision event
			EventCollision c(p_o, p_temp_o, where);

			//send collision event to object's event handler
			p_o->eventHandler(&c);
			p_temp_o->eventHandler(&c);

			//if both hard, collision. No move allowed
			if (p_o->getSolidness() == HARD && p_temp_o->getSolidness() == HARD)
				do_move = false;
			i->next();

			if (!do_move)
				return -1; //move not allowed
		}
	}
	p_o->setPosition(where); //if here, no collision. Allow Move
	return 0;
}

//update()
//update game world
void WorldManager::update() {
	GraphicsManager &gm = GraphicsManager::getInstance();
	LogManager &lm = LogManager::getInstance();

	lm.writeLog("\n***INSIDE WORLDMANAGER UPDATE()***");

	//Iterate through Delete List
	//Delete objects in delete list from memory 
	const ObjectList * dl_p = &deleteList; //pointer to delete list
	ObjectListIterator *di = new ObjectListIterator(dl_p);
	di->first();
	lm.writeLog("Deleting objects");
	while (!di->isDone()) {
		lm.writeLog("delete list iteration %i", di->index);
		gameList.remove(di->currentItem());
		di->next();
	}
	deleteList.clear();

	/***Update Object Positions***/
	//NOTE! Maintain an update list later on instead of iterating across every object
	const ObjectList * gl_p = &gameList; //pointer to game list
	ObjectListIterator *gi = new ObjectListIterator(gl_p);
 
	gi->first();
	while (!gi->isDone()) {
		lm.writeLog("Game list update iteration %i", gi->index);

		//Velocity steps of current item (number of spaces item should move)
		int x = gi->currentItem()->getXVelocityStep();
		int y = gi->currentItem()->getYVelocityStep();

		lm.writeLog("VELOCITY X STEP: %i, VELOCITY Y STEP: %i", x, y);

		if (x != 0 || y != 0) {
			//if object has moved, set new position
			Position old_pos = gi->currentItem()->getPosition();
			Position new_pos;
			new_pos.setX(old_pos.getX() + x);
			new_pos.setY(old_pos.getY() + y);

			//set new object position.
			moveObject(gi->currentItem(), new_pos);
			//gi->currentItem()->setPosition( new_pos );

			// Out Event
			int posX = new_pos.getX();
			int posY = new_pos.getY();
			if (posX < 0 || posX > gm.getXBound() ||
			    posY < 0 || posY > gm.getYBound() - 2)
			{
				EventOut out;
				gi->currentItem()->eventHandler(&out);
			}

			lm.writeLog("WM udpate:\n  new xpos: %d", new_pos.getX());

			/*
			Position objpos = gi->currentItem()->getPosition();
			char objch = gi->currentItem()->getSprite();						
			IF within world boundries, Update the graphics
			if (((old_pos.getX() < gm.getXBound() - 1) && (old_pos.getX() > 1))
					&& ((old_pos.getY() < gm.getYBound() - 1)
							&& (old_pos.getY() > 1))) {
			gm.writeChar(objpos, objch, COLOR_WHITE);
			}
			*/
		}
		gi->next();
	}
	lm.writeLog("****Bottom of worldmanager.update()****");
}

bool WorldManager::isValid(string event_name) {
	// takes the collision and out events
	if (event_name == OUT_EVENT || event_name == COLLISION_EVENT) {
		return true;
	}
	else return false;

}


