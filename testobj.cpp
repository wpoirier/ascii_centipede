//testobj.cpp

#include "testobj.h"
#include <stdlib.h>

TestObj::() {
	n = rand() % 10;

	int x = rand() % 20;
	int y = rand() % 30;
	Position r_p = new Position(x,y);
	setPosition(r_p); //generate a random new position
}

~TestObj::() {}

void TestObj::Move() {
	//check for step event
	//then increment x and y by one
}
