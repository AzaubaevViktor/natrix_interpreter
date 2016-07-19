cmake_minimum_required(VERSION 3.5)
project(natrix_interpreter)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(SOURCE_FILES main.c natrix_object.c interpreter.c errors.c dynamic_array.c native_dict.c natrix.h bytecode_debug.c bytecode_debug.h)
add_executable(natrix_interpreter ${SOURCE_FILES})