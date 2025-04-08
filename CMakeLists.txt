cmake_minimum_required(VERSION 3.29)
project(lab11 C)

set(CMAKE_C_STANDARD 23)

add_executable(lab11 main.c
        functions.c
        functions.h
        stack.h
        tasks.c
        tasks.h)
