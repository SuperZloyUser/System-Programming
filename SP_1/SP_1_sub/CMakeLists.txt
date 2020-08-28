cmake_minimum_required(VERSION 3.10)
project(SP_1_sub C)

set(CMAKE_C_STANDARD 99)

add_executable(SP_1_sub main.c tests.c tests.h fuctions.c fuctions.h)

add_subdirectory(cunit-master)

target_link_libraries(SP_1_sub PRIVATE cunit)