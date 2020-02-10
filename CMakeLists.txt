cmake_minimum_required(VERSION 3.0)
project(Simple-Snake VERSION 0.1 LANGUAGES C)
add_executable(simple-snake main.c snake.c snake.h)
target_link_libraries(simple-snake PRIVATE ncurses)

