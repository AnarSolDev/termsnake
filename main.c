#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ncurses.h>
#include "snake.h"

#define MIN_CHAR_HEIGHT GRID_LINES + 2
#define MIN_CHAR_WIDTH  GRID_COLS * 2
#define GAME_TITLE "TermSnake"
#define GAME_OVER "Game Over"
#define FRAME_PER_SECOND 30
#define MICRO_PER_FRAME 1e3 / FRAME_PER_SECOND

enum colors {
    SNAKE_COLOR = 1,
    FOOD_COLOR,
    OBSTACLES_COLOR,
    POLICE_COLOR,
};

void render_cell(int y, int x)
{
    mvaddch(y, x, ' ');
    mvaddch(y, x + 1, ' ');
}

void render_obstacles(int begin_line, int begin_col)
{
    int i;

    attron(COLOR_PAIR(OBSTACLES_COLOR));
    for (i = 0; i < OBSTACLES_COUNT; i++) {
        render_cell(begin_line + get_obstacles()[i].y,
            begin_col + get_obstacles()[i].x * 2);
    }
    attroff(COLOR_PAIR(OBSTACLES_COLOR));
}

void render_snake(int begin_line, int begin_col)
{
    int i;

    attron(COLOR_PAIR(SNAKE_COLOR));
    for (i = 0; i < get_snake_length(); i++) {
        render_cell(begin_line + get_snake()[i].y,
            begin_col + get_snake()[i].x * 2);
    }
    attroff(COLOR_PAIR(SNAKE_COLOR));
}

void render_food(int begin_line, int begin_col)
{
    attron(COLOR_PAIR(FOOD_COLOR));
    render_cell(begin_line + get_food().y, begin_col + get_food().x * 2);
    attroff(COLOR_PAIR(FOOD_COLOR));
}

void render_information(int begin_line, int begin_col)
{
    attron(COLOR_PAIR(POLICE_COLOR));
    mvaddstr(begin_line - 1, begin_col, GAME_TITLE);
    mvprintw(begin_line + GRID_LINES, begin_col, "Score: %d", get_score());
    attroff(COLOR_PAIR(POLICE_COLOR));
}

void render_game_over(void)
{
    attron(COLOR_PAIR(POLICE_COLOR));
    mvaddstr(LINES / 2, (COLS - strlen(GAME_OVER)) / 2, GAME_OVER);
    attroff(COLOR_PAIR(POLICE_COLOR));
}

void render_game(void)
{
    int grid_begin_line, grid_begin_col;

    grid_begin_line = (LINES - GRID_LINES) / 2;
    grid_begin_col = (COLS - GRID_COLS * 2) / 2;

    erase();
    render_obstacles(grid_begin_line, grid_begin_col);
    render_snake(grid_begin_line, grid_begin_col);
    render_food(grid_begin_line, grid_begin_col);
    render_information(grid_begin_line, grid_begin_col);
    refresh();
}

void init_graphics(void)
{
    if (initscr() == NULL) {
        exit(EXIT_FAILURE);
    }
    if (start_color() == ERR) {
        fputs("Error: error when starting color mode", stderr);
        endwin();
        exit(EXIT_FAILURE);
    }
    if (LINES < MIN_CHAR_HEIGHT || COLS < MIN_CHAR_WIDTH) {
        fprintf(stderr, "Error: the terminal must be at least %d characters "
            "high, and %d characters wide\n", MIN_CHAR_HEIGHT, MIN_CHAR_WIDTH);
        endwin();
        exit(EXIT_FAILURE);
    }
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    init_pair(SNAKE_COLOR, COLOR_WHITE, COLOR_GREEN);
    init_pair(FOOD_COLOR, COLOR_WHITE, COLOR_RED);
    init_pair(OBSTACLES_COLOR, COLOR_WHITE, COLOR_CYAN);
    init_pair(POLICE_COLOR, COLOR_WHITE, COLOR_BLACK);
}

void main(void)
{
    int quit;
    clock_t previous;
    double lag;

    init_graphics();
    init_game();
    quit = 0; 
    previous = clock();
    lag = 0.0;
    while (!quit) {
        clock_t current;
        double elapsed;
        double speed;

        current = clock();
        elapsed = ((double) (current - previous) / CLOCKS_PER_SEC) * 1e3;
        previous = current;
        lag += elapsed;

        switch (getch()) {
            case KEY_LEFT:
                turn_left();
                break;
            case KEY_RIGHT:
                turn_right();
                break;
            case KEY_UP:
                turn_up();
                break;
            case KEY_DOWN:
                turn_down();
                break;
            case 'q':
            case 'Q':
                quit = 1;
                break;
        }

        while (lag >= (speed = get_speed())) {
            if (update_game()) {
                render_game_over();
                nodelay(stdscr, FALSE);
                getch();
                quit = -1;
            }
            lag -= speed;
        }

        render_game(); 
    }

    endwin();
    exit(EXIT_SUCCESS);
}

