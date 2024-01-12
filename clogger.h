#ifndef CLOGGER_H
#define CLOGGER_H
#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef CLOGGER_USE_COLOR
#define CLOGGER_USE_COLOR 0
#endif

typedef enum {
    TRACE,
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL
} loglvl;

typedef struct {
    char* time;
    loglvl level;
    const char* fname;
    int line;
    const char* format;
    va_list args;
} log_event;


void set_log_limit(loglvl lv);
void set_logger_quiet(bool q);
/* Note: closes old files when new one is passed, pass NULL to close previous */
void set_logger_outfile(char* fp);

void clogger_log(loglvl level, const char* src, int line, const char* message, ...);

#define FILENAME (__FILE__ + SOURCE_PATH_SIZE)

#define trace_log(...)  clogger_log(TRACE,  FILENAME, __LINE__, __VA_ARGS__)
#define debug_log(...)  clogger_log(DEBUG,  FILENAME, __LINE__, __VA_ARGS__)
#define info_log(...)   clogger_log(INFO,   FILENAME, __LINE__, __VA_ARGS__)
#define warn_log(...)   clogger_log(WARN,   FILENAME, __LINE__, __VA_ARGS__)
#define error_log(...)  clogger_log(ERROR,  FILENAME, __LINE__, __VA_ARGS__)
#define fatal_log(...)  clogger_log(FATAL,  FILENAME, __LINE__, __VA_ARGS__)

#endif // CLOGGER_H
