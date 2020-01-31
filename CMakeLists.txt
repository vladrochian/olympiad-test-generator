cmake_minimum_required(VERSION 3.15)
project(olympiad_test_generator)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--stack,10000000")

add_executable(olympiad_test_generator main.cpp generator.h example_generator.h utils.h utils.cpp example_generator_with_official_solution.h)