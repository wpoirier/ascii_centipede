#ifndef __OBJECTLIST_H__
#define __OBJECTLIST_H__

//objectlist.h

#define MAX_OBJECTS 100 
#include "object.h"

class ObjectListIterator;

class ObjectList: public Object {

//  private: //made public for testing purposes only
public:

	int count; //number of objects currently in list
	Object *list[MAX_OBJECTS]; //array of pointers to objects

	ObjectList();
	~ObjectList();

	//insert object pointer in list
	//return 0 for sucess, -1 for failure
	int insert(Object *p_obj);

	//remove object object pointer from list
	//return 0 if found, -1 if not
	int remove(Object *p_obj);

	//return total count of objects in the list
	int getCount(void);

	//clear list
	//set count to zero
	int clear();

	//return true if list is empty (else false)
	bool isEmpty();

	//return true if list is full (else false)
	bool isFull();

};

#endif
