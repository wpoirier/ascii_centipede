//testobj.h
//A game object to test the engine

#include "object.h"

class TestObj: public Object {

public:

	int n; //a property to be accessed

	TestObj(); //constructor
	~TestObj(); //destructor

	void Move(); //position is incremented on step event

};

