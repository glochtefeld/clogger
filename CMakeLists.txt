cmake_minimum_required(VERSION 3.16)
project(clogger
    VERSION 0.1.0
    DESCRIPTION "A simple C logging library"
    LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Logger Required Definitions
string(LENGTH "${CMAKE_SOURCE_DIR}/" SOURCE_PATH_SIZE)
add_definitions("-DSOURCE_PATH_SIZE=${SOURCE_PATH_SIZE}")
add_definitions("-DCLOGGER_USE_COLOR=1")

add_library(clogger 
    include/clogger.h
    src/clogger.c)
target_include_directories(clogger PUBLIC include)
