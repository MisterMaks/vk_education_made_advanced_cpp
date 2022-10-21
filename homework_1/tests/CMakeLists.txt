cmake_minimum_required(VERSION 3.14)
project(test_filter)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fprofile-arcs -ftest-coverage -O0")
if(WITH_COVERAGE)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )
else()
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -O3" )
endif()

file(GLOB SOURCES *.cpp)

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${FILTER_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${FILTER_LIB_LIBRARIES} GTest::gtest_main)

# add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
gtest_discover_tests(${PROJECT_NAME})
