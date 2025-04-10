cmake_minimum_required(VERSION 3.28)
project(C_ToBits)

find_package(ALSA REQUIRED)
if(NOT ALSA_FOUND)
    message(SEND_ERROR "Failed to find ALSA-lib")
    return()
else()
    include_directories(${ALSA_INCLUDE_DIRS})
endif()

set(CMAKE_CXX_STANDART 17)

set(ALSA_MIXER_LIB alsa_mixer.c)
set(OPERATE_EXE operate.c)
set(LIST_EXE list.c)

add_library(GCS.AlsaMixer STATIC ${ALSA_MIXER_LIB})

add_executable(C_ALSA_LIST ${LIST_EXE})
add_executable(C_ALSA_OPERATE ${OPERATE_EXE})

target_link_libraries(C_ALSA_LIST GCS.AlsaMixer ALSA::ALSA)
target_link_libraries(C_ALSA_OPERATE GCS.AlsaMixer ALSA::ALSA)

set_target_properties(C_ALSA_LIST PROPERTIES OUTPUT_NAME "C. ALSA-Mic-dB. List")
set_target_properties(C_ALSA_OPERATE PROPERTIES OUTPUT_NAME "C. ALSA-Mic-dB. Operate")
