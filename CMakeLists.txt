cmake_minimum_required(VERSION 3.5)
project(natrix_interpreter)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(SOURCE_FILES main.cpp natrix_object.cpp natrix_object.h interpreter.cpp interpreter.h errors.cpp dynamic_array.cpp dynamic_array.h)
add_executable(natrix_interpreter ${SOURCE_FILES})