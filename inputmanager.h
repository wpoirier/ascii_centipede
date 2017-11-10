//inputmanager.h

#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__

#include "manager.h"
#include <ncurses.h>
#include <string>
	
class InputManager : public Manager {

private:
	InputManager(InputManager const&); //do not alow copy
	void operator=(InputManager const&); //do not allow assignment
	InputManager(); //private constructor because its a singleton

public:
	static InputManager & getInstance();
	~InputManager(); //destructor

	//start up and shutdown functions
	int startUp();
	int shutDown();

	//keys
	int getKey();
	//int keyTrigger( char* press_type);//event handler for a key press or release.
	//parameter is a string indicating when you want the key registered.
	//"press" for a key press or "release" for a key being released.

	//mouse
	int mouseClick(char* button); //mouse click event handler.
	//enter a string "left" or "right" for which mouse button to use.
	bool isValid(string event_name);
};

#endif

