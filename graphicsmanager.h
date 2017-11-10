//graphicsmanager.h

#ifndef __GRAPHICS_MANAGER_H__
#define __GRAPHICS_MANAGER_H__

#include "manager.h"
#include "position.h"

#include <string>

#ifdef CYGWIN
#include <ncurses/curses.h>
#else
#include <ncurses.h>
#endif

#define COLOR_DEFAULT COLOR_WHITE

#define LEFT_JUSTIFIED 0
#define RIGHT_JUSTIFIED 1
#define CENTER_JUSTIFIED 2
typedef int Justification;

class GraphicsManager : public Manager {

private:
	GraphicsManager(GraphicsManager const&); //don't allow copy
	void operator =(GraphicsManager const&); //don't allow assignment
	GraphicsManager(); //private construct since singleton

	//WINDOW * buffer2;

public:
	virtual ~GraphicsManager(); //destructor

	WINDOW * buffer; //drawing buffer

	//get singleton instance of Graphics Mangager
	static GraphicsManager &getInstance();

	int startUp();
	int shutDown();

	
	void writeChar(Position pos, char ch, int color = COLOR_DEFAULT);
	void deleteChar(Position pos);

	int drawString(Position pos, string str, Justification just, int color = COLOR_DEFAULT);

	//return horizontal (right) boundryg
	int getXBound();  

	//return vertical (bottom) boundry
	int getYBound();

	bool isValid(string event_name);

	//render current display buffer
	// return 0 if ok, else -1
	int swapBuffers();
	void clear();
	//return curses drawing window
	WINDOW *getBuffer();

	int max_x;
	int max_y;
};

#endif

