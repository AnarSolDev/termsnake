cmake_minimum_required(VERSION 3.0)
project(TermSnake VERSION 0.1 LANGUAGES C)
add_executable(termsnake main.c snake.c snake.h)
target_link_libraries(termsnake PRIVATE ncurses)
set_property(TARGET termsnake PROPERTY C_STANDARD 90)

