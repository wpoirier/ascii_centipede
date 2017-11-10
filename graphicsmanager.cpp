//graphicsmanager.cpp

#include "graphicsmanager.h"

GraphicsManager::GraphicsManager() {
}
GraphicsManager::~GraphicsManager() {
}

GraphicsManager &GraphicsManager::getInstance() {
	static GraphicsManager instance;
	return instance;
}

int GraphicsManager::startUp() {
	initscr(); //init curses mode

	max_x = getXBound();
	max_y = getYBound();

	buffer = newwin(0,0,0,0); //init full size window for drawing buffer

	int checkOk = clearok(buffer, TRUE);

	int checkLeave = leaveok(buffer, TRUE);

	if (has_colors() == TRUE) 
	{
		start_color();	
		init_pair(COLOR_RED, COLOR_RED, COLOR_BLACK);
		init_pair(COLOR_GREEN, COLOR_GREEN, COLOR_BLACK);
		init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
		init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);
		init_pair(COLOR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
		init_pair(COLOR_CYAN, COLOR_CYAN, COLOR_BLACK);
		init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_BLACK);
	}
	
	int checkBold = wattron(buffer, A_BOLD);
	
	if (
		checkOk == ERR ||
		checkLeave == ERR ||
		checkBold == ERR
		)
	{
		is_started = false;
		return -1;
	}
	
	is_started = true;
	
	curs_set(0); //turn off cursor
	noecho(); //don't echo chars to terminal
	
	return 0;
}

int GraphicsManager::shutDown() {
	curs_set(1);
	endwin();
	return 0;
}

void GraphicsManager::writeChar(Position pos, char ch, int color) {
	int x = pos.getX();
	int y = pos.getY();

	wattron(buffer, COLOR_PAIR(color));
	mvwaddch(buffer, y, x, ch);
	wattroff(buffer, COLOR_PAIR(color));
}

void GraphicsManager::deleteChar(Position pos) {
	int x = pos.getX();
	int y = pos.getY();

	move(y, x);
	delch();
//	refresh();
}

int GraphicsManager::drawString(Position pos, string str, Justification just, int color){
	//get start position
	Position starting_pos = pos;
	switch (just){
		case CENTER_JUSTIFIED:
			starting_pos.setX( pos.getX() - str.size() / 2 );
			break;
		case RIGHT_JUSTIFIED:
			starting_pos.setX( pos.getX() - str.size() );
			break;
		case LEFT_JUSTIFIED:
			default:
			break;
	}

	for (int i = 0; i < str.size(); i++){
		Position temp_pos(starting_pos.getX() + i, starting_pos.getY());
		writeChar(temp_pos, str[i], color);
	}

	return 0;
}

int GraphicsManager::getXBound() {
	getmaxyx(stdscr, max_y, max_x);
	return max_x;
}

int GraphicsManager::getYBound() {
	getmaxyx(stdscr, max_y, max_x);
	return max_y;
}

bool GraphicsManager::isValid(string event_name) {
	// takes no events
	return false;
}

int GraphicsManager::swapBuffers(){

	wrefresh(buffer); //refresh display buffer
//	werase(buffer); //erase current image of buffer
//	clearok(buffer, true);//clear display buffer

}

void GraphicsManager::clear(){
	werase(buffer);
}

