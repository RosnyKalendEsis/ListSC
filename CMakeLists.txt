cmake_minimum_required(VERSION 3.23)
project(ListSC C)

set(CMAKE_C_STANDARD 99)

add_executable(ListSC main.c primitive.c headers/primitive.h)
