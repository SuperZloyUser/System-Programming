cmake_minimum_required(VERSION 3.10)

project(SP_5_SERVER C)

set(CMAKE_C_STANDARD 99)

add_executable(SP_5_SERVER main.c Server.c Server.h ../functions.c ../functions.h OutFuncs.c OutFuncs.h)

target_link_libraries(SP_5_SERVER ws2_32)