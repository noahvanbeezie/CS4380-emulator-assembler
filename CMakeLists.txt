cmake_minimum_required(VERSION 3.14)
project(Project1)

set(CMAKE_CXX_STANDARD_14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
	emu4380
	src/main.cpp src/emu4380.cpp include/emu4380.h
)

include(FetchContent)
FetchContent_Declare(
	googletest
	URL
	https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
	runTests
	myTests.cpp src/emu4380.cpp include/emu4380.h
)
target_link_libraries(
	runTests
	GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(runTests)
