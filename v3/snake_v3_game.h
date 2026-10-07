#ifndef SNAKE_V3_GAME_H
#define SNAKE_V3_GAME_H

#define MAX_WIDTH 100
#define MAX_HEIGHT 40
#define MAX_SNAKE 4000

extern int snake_length;
extern int head_index;

extern int snake_x[MAX_SNAKE];
extern int snake_y[MAX_SNAKE];

enum Action
{
    ACTION_STRAIGHT,
    ACTION_LEFT,
    ACTION_RIGHT
};

void action_to_direction(
    int action,
    int old_dx, int old_dy,
    int *new_dx, int *new_dy
);

void get_left_direction(
    int dx, int dy,
    int *new_dx, int *new_dy
);

void get_right_direction(
    int dx, int dy,
    int *new_dx, int *new_dy
);

int is_snake_position(int x, int y);

int is_safe_move(
    int new_head_x, int new_head_y,
    int food_x, int food_y,
    int width, int height
);

void move_one_step(
    char board[MAX_HEIGHT][MAX_WIDTH],
    int width, int height,
    int new_head_x, int new_head_y,
    int *food_x, int *food_y,
    int *score
);

void print_board(
    char board[MAX_HEIGHT][MAX_WIDTH],
    int width, int height,
    int score
);

#endif
