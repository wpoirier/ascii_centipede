//logmanager.cpp

#include "logmanager.h"

//#include <string.h>

LogManager::LogManager() {
} //:Manager(){}
LogManager::~LogManager() {
}

LogManager &LogManager::getInstance() {
	static LogManager single_instance;
	return single_instance;
}

int LogManager::startUp(bool flush_on) {

	p_f = fopen(LOGFILE_NAME, "w"); //open logfile
	fprintf(p_f, "LOGFILE OPENED!\n"); //test log
	do_flush = flush_on;
	is_started = true;
}

int LogManager::shutDown() {
	fclose(p_f); //close logfile
	return 0;
}

void LogManager::writeLog(const char* fmt, ...) {
	fprintf(p_f, "\nLogMessage: ");
	va_list args;
	va_start(args, fmt);
	vfprintf(p_f, fmt, args); //testing multiple args
	va_end(args);

	if (do_flush)
		fflush(p_f);
}

bool LogManager::isValid(string event_name) {
	// takes no events
	return false;
}


