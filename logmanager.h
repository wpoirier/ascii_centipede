#ifndef __LOG_MANAGER_H__
#define __LOG_MANAGER_H__

//due to formatting errors and other issues, I wrote a different version of
//the logmanager using C++'s iostream and fstream

#include "manager.h"
#include <stdio.h>
#include <stdarg.h>

#define LOGFILE_NAME "dragonflylog.txt"

class LogManager{// : public Manager {

private:
	LogManager(); //private constructor because its a singleton
	LogManager(LogManager const&); //do not allow copy
	void operator=(LogManager const&); //do not allow assignment

	bool do_flush; //true if fflush after write
	FILE *p_f; //pointer to log file structure
	char* getTimeString();
	bool is_started;

public:

	static LogManager &getInstance(); //get single instance of logmanager
	~LogManager();

	//input true to turn on file flushing
	//open log file
	int startUp(bool flush_on);

	//close log file
	int shutDown();

	//Write to logfile. 
	void writeLog(const char * fmt, ...);

	bool isValid(string event_name);
};

#endif
