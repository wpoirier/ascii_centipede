//position.h

#ifndef POSITION_H_
#define POSITION_H_

class Position {

public:
	int x;
	int y;

	Position(); //by default, position set to (0,0)
	Position(int, int); //set 2D position (x,y) of a new object
	~Position(); //destructor

	int getX(); //get x cord. of object
	void setX(int new_x); //set new x position of object
	int getY();
	void setY(int new_y);
};

#endif
