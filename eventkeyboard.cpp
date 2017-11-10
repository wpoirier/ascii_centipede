//eventkeyboard.cpp

#include "eventkeyboard.h"

#include "logmanager.h"

EventKeyboard::EventKeyboard() {
	this->event_type = KEYBOARD_EVENT;
//  key = NULL;
}

void EventKeyboard::setKey(char new_key) {
	key = new_key;
		LogManager &lm = LogManager::getInstance();
		lm.writeLog("KeyboardEvent.setKey -- key set to: %c", key);

}

char EventKeyboard::getKey() {
	return key;
}
