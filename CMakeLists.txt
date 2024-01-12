cmake_minimum_required(VERSION 3.16)
project(clogger
    VERSION 0.1.0
    DESCRIPTION "A simple C logging library"
    LANGUAGES C)

# Logger Required Definitions
add_definitions("-DCLOGGER_USE_COLOR=1")

add_library(clogger 
    clogger.h
    clogger.c)
