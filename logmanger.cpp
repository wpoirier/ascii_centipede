#ifndef __LOG_MANAGER_H__
#define __LOG_MANAGER_H__

#include "manager.h"

#include <stdio.h>
#include <stdarg.h>

#define LOGFILE_NAME "dragonfly.log"

class LogManager: public Manager {

private:
	LogManager(LogManager const&);    ///< Don't allow copy.
	void operator=(LogManager const&); ///< Don't allow assignment.
	LogManager();                      ///< Private since a singleton.

protected:
	bool do_flush;                     ///< True if fflush after each write.
	FILE *fp;                          ///< Pointer to log file.
	char *getTimeString();            ///< Returns pretty-formatted string.

public:
	~LogManager();
	static LogManager &getInstance(); //get the one (only) instance of logmanager

	int startUp();
	int shutDown();
	void writeLog(const char* fmt, ...);
};

#endif
