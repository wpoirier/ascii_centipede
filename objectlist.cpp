//objectlist.cpp

#include "objectlist.h"
#include "logmanager.h"
#include "graphicsmanager.h"

ObjectList::ObjectList() {

	//LogManager &lm = LogManager::getInstance();
	//lm.writeLog("ObjecList constructor\n");
	//initialize list to null
	for (int i = 0; i <= MAX_OBJECTS - 1; ++i) {
		list[i] = 0;
		//lm.writeLog("list[%d]: ", i, list[i]);
	}
	count = 0;
	//lm.writeLog("bottom of object list constructor\n");
}
ObjectList::~ObjectList() {
	clear(); //clear object list
}

//insert object pointer in list
//return 0 for sucess, 1 for empty/full, -1 for error
int ObjectList::insert(Object *p_obj) {

	LogManager &lm = LogManager::getInstance();

	//exit if list is full 
	if (count == MAX_OBJECTS)
		return 1;

	list[count] = p_obj;
	count++;
	lm.writeLog("inserted object %p", p_obj);
	return 0; //successfully inserted
	
/*
	lm.writeLog("err: Did NOT insert object %p", p_obj);
	return -1; //error
*/
}

//remove object pointer from list
//return 0 if found, -1 if not
int ObjectList::remove(Object *p_obj) {
	//list is empty
	if (count == 0)
		return 1;

	//remove object
	for (int i = 0; i <= (count); i++) {

		if (list[i] == p_obj) { //if spot in list equals p_obj

			list[i] = NULL;
			//rearange all objects past this one over
			for (int j = i; j < count - 1; j++) {
				//NOTE: condition check for end of list
				list[j] = list[j + 1];
				list[j+1] = NULL;
			}
			count--;
			GraphicsManager &gm = GraphicsManager::getInstance();
			gm.deleteChar(p_obj->getPosition());
			return 0; //successfully removed
		}
	}
	return -1; //object not removed
}

//return total count of objects in the list
int ObjectList::getCount(void) {
	return count;
}

//clear list
int ObjectList::clear() {

	if (isEmpty())
		return 1; //return, object list is empty

	//iterate through list and set everything to zero
	for (int i = 0; i <= count; i++) {
		list[i] = 0;
	}

	count = 0;
	return 0;
}

//return true if list is empty (else false)
bool ObjectList::isEmpty() {
	if (count == 0) //object count is zero
		return true;
	return false;
}

//return true if list is full (else false)
bool ObjectList::isFull() {
	if (count == MAX_OBJECTS)
		return true;
	return false;
}

