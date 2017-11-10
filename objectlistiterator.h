#ifndef __OBJECTLISTITERATOR_H__
#define __OBJECTLISTITERATOR_H__

//objectlistiterator.h

#include "objectlist.h"

class ObjectList;

class ObjectListIterator {

private:
	ObjectListIterator(); //must be given list when created
//   int index; //index to array list
	const ObjectList* p_list; //list iterating over

public:

	int index;

	//create iterator over the indicated list
	ObjectListIterator(const ObjectList *p_l);

	//set iterator to first item in the list
	void first();

	//set iterator to next item in the list
	void next();

	//return true when reached end of the list
	bool isDone();

	//return pointer to current item in list
	Object* currentItem();

};

#endif
