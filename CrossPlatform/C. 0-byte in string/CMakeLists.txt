cmake_minimum_required(VERSION 3.28)
project(C_0byte_in_string)

set(CMAKE_CXX_STANDART 17)

set(MAIN_EXE main.c)

add_executable(C_0BYTE_IN_STRING ${MAIN_EXE})

set_target_properties(C_0BYTE_IN_STRING PROPERTIES OUTPUT_NAME "C. 0-byte in string")
