cmake_minimum_required(VERSION 3.28)
project(C_CPP_Exps)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin/${CMAKE_SYSTEM_NAME})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/build/lib/${CMAKE_SYSTEM_NAME})

add_subdirectory("CrossPlatform")

if (WIN32)
    add_subdirectory("Windows")
elseif (UNIX)
    add_subdirectory("Unix")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    add_subdirectory("MacOS")
endif ()
