//objectlistiterator.cpp

#include "objectlistiterator.h"

//class ObjectList;

ObjectListIterator::ObjectListIterator(const ObjectList *p_l) {
	index = MAX_OBJECTS - 1; //set index to maximum number of allowed elements. Offset by minus 1 since data type is an array
	p_list = p_l; //set p_list to the given list
	first();
}

void ObjectListIterator::first() {
	index = 0;
}

void ObjectListIterator::next() {
	++index;
}

bool ObjectListIterator::isDone() {

	if (p_list->count == 0)
		return true;

	if (index == (p_list->count))
		return true;
	else
		return false;
}

Object* ObjectListIterator::currentItem() {
	return p_list->list[index];
}
