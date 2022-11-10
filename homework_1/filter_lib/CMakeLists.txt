cmake_minimum_required(VERSION 3.0.0)
project(filter_lib)

if(USE_SANITIZER)
set(CMAKE_EXE_LINKER_FLAGS "-fsanitize=address,undefined -fno-sanitize-recover=all -fsanitize-undefined-trap-on-error -fprofile-arcs -ftest-coverage -O0 -g")
else()
set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage -O0")
endif()

if(WITH_COVERAGE)
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-fprofile-arcs -ftest-coverage -fPIC -O0")
else()
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -O3" )
endif()

file(GLOB SOURCES *.c)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

add_library(${PROJECT_NAME} ${SOURCES})

set(FILTER_LIB_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(FILTER_LIB_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)
