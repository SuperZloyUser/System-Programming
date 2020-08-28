cmake_minimum_required(VERSION 3.10)
project(SP_2 C)

set(CMAKE_C_STANDARD 99)

add_executable(SP_2 main.c)

target_link_libraries(SP_2 pthread)