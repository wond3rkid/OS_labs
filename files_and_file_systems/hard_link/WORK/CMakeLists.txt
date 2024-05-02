cmake_minimum_required(VERSION 3.27)
project(hard_link C)

set(CMAKE_C_STANDARD 11)

add_executable(hard_link
        main.c
        file_dir_handler.h
        file_dir_handler.c
        links_handler.c
        links_handler.h)
