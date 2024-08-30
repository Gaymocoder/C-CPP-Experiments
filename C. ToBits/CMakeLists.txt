cmake_minimum_required(VERSION 3.28)
project(C_ToBits)

set(CMAKE_CXX_STANDART 17)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)

set(ENDIANNESS_LIB endianness.c)
set(BITS_LIB bits.c)
set(MAIN_EXE main.c)

add_executable(C_TO_BITS ${MAIN_EXE} ${BITS_LIB} ${ENDIANNESS_LIB})

set_target_properties(C_TO_BITS PROPERTIES OUTPUT_NAME "C. ToBits")