cmake_minimum_required(VERSION 3.27)
project(lab C)

set(CMAKE_C_STANDARD 11)

add_executable(lab
        dir_handler.c
        dir_handler.h
        main.c
        file_handler.c
        file_handler.h)
