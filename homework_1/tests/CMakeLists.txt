cmake_minimum_required(VERSION 3.14)
project(test_filter)

# set(CMAKE_CXX_STANDARD 11)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

if(USE_SANITIZER)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fsanitize=address,undefined -fno-sanitize-recover=all -fsanitize-undefined-trap-on-error -fprofile-arcs -ftest-coverage -O0 -g")
else()
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fprofile-arcs -ftest-coverage -O0")
endif()

if(WITH_COVERAGE)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )
else()
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -O3" )
endif()

file(GLOB SOURCES *.cpp)

# find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${FILTER_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${FILTER_LIB_LIBRARIES} GTest::gtest_main)

# add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
gtest_discover_tests(${PROJECT_NAME})
