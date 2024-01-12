# Clogger - A C Logging Library
These can't be too difficult to make, right?

Anyway, this is just a fun weekend project to see how/what I can make with this. There's probably a more robust system out there, but this should be a dead simple one to use.

The goal of this project is to make a logging library in one weekend (or so) that can:
* Write to a given log file ✅
* Output to stdout/stderr with optional ANSI colors ✅
* limit log levels ✅

## Usage
Add the following #defines somewhere in your project: `CLOGGER_USE_COLOR=1` (or 0 for no color) and `SOURCE_PATH_SIZE=X` where X is the length (in characters of the root directory of your project. 

If you use CMake, add the following definitions to the root of your cmake project.
```cmake
# Logger Required Definitions
string(LENGTH "${CMAKE_SOURCE_DIR}/" SOURCE_PATH_SIZE)    # required 
add_definitions("-DSOURCE_PATH_SIZE=${SOURCE_PATH_SIZE}") # required
add_definitions("-DCLOGGER_USE_COLOR=1")
```

Next, `#include clogger.h` in any file you'd like to log in. To log at a particular level, use one of the following macros:
```c
trace_log("Drop in replacement for printf: %s", "this"); // trace
debug_log("Drop in replacement for printf: %s", "this"); // debug
info_log("Drop in replacement for printf: %s", "this"); // info
warn_log("Drop in replacement for printf: %s", "this"); // warn
error_log("Drop in replacement for printf: %s", "this"); // error
fatal_log("Drop in replacement for printf: %s", "this"); // fatal
```

The macros will automatically print to stderr in the following format:

`[Time] [Level] [file:line] -> [Message]`

Logging to a file:
```c
set_logger_outfile("my-log.txt"); // Creates file if needed and appends logs
// ...
set_logger_outfile("my-other-log.txt"); // Closes the first file and opens the new one
// ...
set_logger_outfile(NULL); // Closes the last file
```

Setting a logging threshhold:
```c
set_log_limit(WARN); // Only logs with the level WARN or above will be logged, 
                     // e.g. no TRACE/DEBUG/INFO
```

Suppressing stderr output: `set_logger_quiet(true)` or `set_logger_quiet(false)`
