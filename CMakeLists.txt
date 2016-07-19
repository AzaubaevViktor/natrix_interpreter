cmake_minimum_required(VERSION 3.5)
project(natrix_interpreter)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(SOURCE_FILES main.c natrix_object.c natrix_object.h interpreter.c interpreter.h errors.c dynamic_array.c dynamic_array.h namespace.c namespace.h bytecode_debug.c bytecode_debug.h)
add_executable(natrix_interpreter ${SOURCE_FILES})