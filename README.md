# TermSnake - Terminal Based Snake Game

TermSnake is a simple implementation of the famous [Snake game](https://en.wikipedia.org/wiki/Snake_(video_game_genre)).

It is developed in C language, and uses the ncurses library to display graphics in console mode.

Conception and implementation choices have been made to make TermSnake a fun C programming mini-project for beginners.

![TermSnake Snake Game](/illustration.gif)

## Commands

* ```LEFT``` orient the snake left
* ```RIGHT``` orient the snake right
* ```UP```	: orient the snake top
* ```DOWN```	: orient the snake down
* ```Q``` or ```q```: quit the game

## Features

* The game area has a fixed size, defined in advance
* The snake's speed increases each time a food is eaten, until reaching a maximum speed
* There is only one level of difficulty. The goal is to achieve the highest score

## Technologies

The project is written in C, fully compatible with C89/C90 standard.

The only dependency of the project is the ncurses library. The project was developed and tested with version 6.1 of ncurses.

## Compile and launch

### Installing CMake

**On Ubuntu 18.04**
```
sudo apt-get install cmake
```

### Installing C compiler

**On Ubuntu 18.04**
```
sudo apt-get install build-essential
```

### Installing ncurses library

**On Ubuntu 18.04**
```
sudo apt-get install libncurses5-dev
```

### Compiling and launching the game

**On Ubuntu 18.04**
```
mkdir build
cd build
cmake -G "Unix Makefiles" <source-dir>
cmake --build .
./termsnake
```
## License
This project is licensed under the terms of the MIT license. You can check out the full license [here](/LICENSE.txt).
