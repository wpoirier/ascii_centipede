//inputmanager.cpp

#include "inputmanager.h"
#include "eventkeyboard.h"
#include "eventmouse.h"

InputManager::InputManager() {
} //:Manager(){}
InputManager::~InputManager() {
}

InputManager & InputManager::getInstance() {
	static InputManager instance;
	return instance;
}

int InputManager::startUp() {

	nodelay(stdscr, TRUE); //non-blockinng input
	cbreak(); //enable cbreak
	nonl(); //so enter key can be used
	noecho(); //don't echo chars to terminal
	mousemask(BUTTON1_CLICKED, NULL);
	keypad(stdscr, TRUE);
	is_started = true;
	return 0;
}

int InputManager::shutDown() {
	curs_set(1);
	return 0;
}

int InputManager::getKey() {

	int ch; //character to be returned when pressed
	ch = getch(); //get character

	if (ch != ERR){
		
		MEVENT m_event;
		//If mouse...
		if (ch == KEY_MOUSE && getmouse(&m_event) == OK){
			//m_event has values
			if (m_event.bstate & BUTTON1_CLICKED){
				//create eventmouse
				EventMouse m;
				m.setMouseX(m_event.x);
				m.setMouseY(m_event.y);
				//m.setMouseAction();
				onEvent(&m);
			}
		}
		
		//...else, Keyboard was pressed
		else{
			//create keyboard event and send ch to it
			EventKeyboard k;
			k.setKey(ch);
			onEvent(&k);
		}
	}


	return ch; //return that character
}

bool InputManager::isValid(string event_name) {
	// takes the keyboard and mouse events
	if (event_name == KEYBOARD_EVENT ||
	    event_name == MOUSE_EVENT){
		return true;
	}
	return false;
}


