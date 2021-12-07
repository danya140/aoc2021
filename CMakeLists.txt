cmake_minimum_required(VERSION 3.19)
project(aoc2021)

set(CMAKE_CXX_STANDARD 14)

MACRO(DIRLIST result curdir)
    FILE(GLOB children RELATIVE ${curdir} ${curdir}/puzzle*)
    SET(dirlist "")
    FOREACH(child ${children})
        IF(IS_DIRECTORY ${curdir}/${child})
            LIST(APPEND dirlist ${child})
        ENDIF()
    ENDFOREACH()
    SET(${result} ${dirlist})
ENDMACRO()

DIRLIST(DIRS ${CMAKE_CURRENT_SOURCE_DIR})

foreach(subdir ${DIRS})
    add_subdirectory(${subdir})
endforeach()

#add_executable(aoc2021 main.cpp)