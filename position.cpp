#include "position.h"

Position::Position() {
	x = 0;
	y = 0;
}

Position::Position(int init_x, int init_y) {
	x = init_x;
	y = init_y;
}

void Position::setX(int xpos) {
	x = xpos;
}

void Position::setY(int ypos) {
	y = ypos;
}

int Position::getX() {
	return x;
}

int Position::getY() {
	return y;
}

Position::~Position() {
	//remove position object
}
