#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include "clogger.h"

static struct {
    loglvl above;
    bool quiet;
    FILE* fileout;
} CloggerOptions = { .above = DEBUG, .quiet=0, .fileout=NULL };

void set_log_limit(loglvl lv) { CloggerOptions.above = lv; }
void set_logger_quiet(bool q) { CloggerOptions.quiet = q; }

static void set_logger_fileout(FILE* fp) {
    if (CloggerOptions.fileout == fp) return;
    if (CloggerOptions.fileout != NULL) fclose(CloggerOptions.fileout);
    CloggerOptions.fileout = fp;
}
void set_logger_outfile(char* filename) {
    if (filename == NULL) { 
        set_logger_fileout(NULL);
        return;
    }
    FILE* out = fopen(filename, "a+");
    if (out == NULL) perror("Warning: could not open log file");
    set_logger_fileout(out);
}

static const char* levels[] = { "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL" };

#if CLOGGER_USE_COLOR
static const char* colors[] = { 
    "\x1b[38;5;33m", // Trace Blue
    "\x1b[38;5;39m", // Debug Light blue
    "\x1b[38;5;34m", // Info Green
    "\x1b[38;5;130m", // Warn Orange
    "\x1b[38;5;160m", // Error Red
    "\x1b[38;5;124m", // Fatal Dark red
};

static const char* RESET = "\x1b[33;0m";
static const char* BORING = "\x1b[38;5;245m";
#endif

#define CLOG_TIME_LENGTH 9
static bool set_time(log_event* l) {
    time_t current = time(NULL);
    if (current == (time_t)(-1))
        current = (time_t)(0);
    struct tm* timeinfo = localtime(&current);
    l->time = malloc(sizeof(char) * CLOG_TIME_LENGTH);
    if (l->time == NULL) return false;
    strftime(l->time, CLOG_TIME_LENGTH, "%H:%M:%S", timeinfo);
    return true;
}


static void clogger_print_out(void* stream, log_event* l, bool print_color) {
    if (stream == NULL || l == NULL) return;
    if (print_color) {
#if CLOGGER_USE_COLOR
        fprintf(stream, 
                "%s%s %s%s\t%s%s:%d\t->%s ",
                BORING, l->time,
                colors[l->level], levels[l->level],
                BORING, l->fname, l->line,
                RESET
        );
#endif
    } else {
        fprintf(stream, "%s %s\t%s:%d\t-> ",
                l->time,
                levels[l->level],
                l->fname, l->line
        );
    }
    vfprintf(stream, l->format, l->args);
    fprintf(stream, "\n");
}

void clogger_log(loglvl level, const char* src, int line, const char* message, ...) {
    if (level < CloggerOptions.above) return;

    log_event l = { 
        .level=level,
        .fname=src,
        .line=line,
        .format=message
    };
    bool was_set = set_time(&l);
    if (!was_set) return; // No need to work with a null ptr

    // 1. Print to file
    va_start(l.args, message);
    clogger_print_out(CloggerOptions.fileout, &l, false);
    va_end(l.args);

    // 2. Print to stdout (if possible)
    if (!CloggerOptions.quiet) {
        va_start(l.args, message);
        clogger_print_out(stderr, &l, CLOGGER_USE_COLOR);
        va_end(l.args);
    }

    free(l.time);
}

/*void clogger_file_log(loglvl level, char to_file, const char* src, int line, const char* fpath, const char* message, ...) {}*/
