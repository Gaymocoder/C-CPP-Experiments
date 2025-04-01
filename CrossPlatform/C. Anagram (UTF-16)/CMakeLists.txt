cmake_minimum_required(VERSION 3.28)
project(C_Anagram)

set(CMAKE_CXX_STANDART 17)

set(GCSIO_LIB gcsio.c)
set(ANAGRAM_LIB anagram.c)
set(MAIN_EXE main.c)

add_executable(C_ANAGRAM ${MAIN_EXE} ${GCSIO_LIB} ${ANAGRAM_LIB})

set_target_properties(C_ANAGRAM PROPERTIES OUTPUT_NAME "C. Anagram")
