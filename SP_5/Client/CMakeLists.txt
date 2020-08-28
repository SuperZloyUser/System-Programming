cmake_minimum_required(VERSION 3.10)

project(SP_5_CLIENT C)

set(CMAKE_C_STANDARD 99)

add_executable(SP_5_CLIENT main.c Client.c Client.h OutFuncs.c OutFuncs.h)