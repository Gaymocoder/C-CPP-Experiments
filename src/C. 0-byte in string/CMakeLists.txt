cmake_minimum_required(VERSION 3.28)
project(C_0byte_in_string)

set(CMAKE_CXX_STANDART 17)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

set(MAIN_EXE main.c)

add_executable(C_0BYTE_IN_STRING ${MAIN_EXE})

set_target_properties(C_0BYTE_IN_STRING PROPERTIES OUTPUT_NAME "C. 0-byte in string")
