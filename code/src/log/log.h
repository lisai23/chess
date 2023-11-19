#ifndef LOG_H
#define LOG_H
#include <string.h>
#include <string>
#include <vector>
#include <stdarg.h>
#include <ctime>
#define __FILENAME__    (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1) : __FILE__)
#define Debug_log(...) debug_log("DEBUG", __FILENAME__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define LOGSIZE 512
#define LOGPATH "/run/log/"
#define CURRENTLOG "/run/log/chess.log"
#define LOGFILESIZE 30*1024*1024

void currenttime(char *buff);

void debug_log(
			const char *logLevel,
			const char *file,
            const char *func,    
            const int   iLine,
            const char *format ,...);

void log_init();

#endif //LOG_H