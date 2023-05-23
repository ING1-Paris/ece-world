cmake_minimum_required(VERSION 3.10)
project(PROJET C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-L/usr/local/lib -lalleg")


add_executable(PROJET main.c utils/tools.c functions/attractions.c functions/checks.c functions/display.c functions/init.c functions/keyboard.c functions/players.c)
