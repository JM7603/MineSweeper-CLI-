cmake_minimum_required(VERSION 3.24)
project(mine_sweeper C)

set(CMAKE_C_STANDARD 11)

add_executable(mine_sweeper main.c mine_sweeper.c mine_sweeper.h)
