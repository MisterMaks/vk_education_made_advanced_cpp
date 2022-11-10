cmake_minimum_required(VERSION 3.0.0)
project(homework_1 VERSION 0.1.0)

option(USE_SANITIZER "Should i use sanitizer" OFF)

add_subdirectory(filter_lib)

message("FILTER_LIB_INCLUDE_DIRS = ${FILTER_LIB_INCLUDE_DIRS}")
message("FILTER_LIB_LIBRARIES = ${FILTER_LIB_LIBRARIES}")

add_executable(${PROJECT_NAME} main.c)

if(USE_SANITIZER)
set(CMAKE_EXE_LINKER_FLAGS "-fsanitize=address,undefined -fno-sanitize-recover=all -fsanitize-undefined-trap-on-error -fprofile-arcs -ftest-coverage -O0 -g")
else()
set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage -O0")
endif()

option(WITH_COVERAGE "Use coverage" OFF)
if(WITH_COVERAGE)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )
else()
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -O3" )
endif()

configure_file(header.in.h header.h)

# file(GLOB SOURCES "*.c")

# add_executable(${PROJECT_NAME} ${SOURCES})

# message("SOURCES = ${SOURCES}")

target_include_directories(${PROJECT_NAME} PUBLIC ${FILTER_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${FILTER_LIB_LIBRARIES})

enable_testing()
add_subdirectory(tests)
