#ifndef SNAKE_V3_GAME_H
#define SNAKE_V3_GAME_H

#define MAX_WIDTH 100
#define MAX_HEIGHT 40
#define MAX_SNAKE 4000

#define STATE_COUNT 128
#define ACTION_COUNT 3

#define REWARD_FOOD 10.0
#define REWARD_DEATH -10.0
#define REWARD_STEP -1.0

#define ALPHA 0.1
#define GAMMA 0.9

extern int snake_length;
extern int head_index;

extern int snake_x[MAX_SNAKE];
extern int snake_y[MAX_SNAKE];

extern double q_table[STATE_COUNT][ACTION_COUNT];

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

int is_action_safe(
    int action,
    int dx, int dy,
    int food_x, int food_y,
    int width, int height
);

void get_danger_info(
    int dx, int dy,
    int food_x, int food_y,
    int width, int height,
    int *danger_straight,
    int *danger_left,
    int *danger_right
);

int encode_danger_state(
    int danger_straight,
    int danger_left,
    int danger_right
);

void get_food_info(
    int dx, int dy,
    int food_x, int food_y,
    int *food_straight,
    int *food_behind,
    int *food_left,
    int *food_right
);

int encode_food_state(
    int food_straight,
    int food_behind,
    int food_left,
    int food_right
);

int combine_state(
    int danger_state,
    int food_state
);

int get_state(
    int dx, int dy,
    int food_x, int food_y,
    int width, int height
);

int choose_best_action(int state);

int choose_random_action(void);

int choose_action(
    int state,
    double epsilon
);

double calculate_reward(
    int died,
    int ate_food
);

double get_max_q_value(int state);

void update_q_value(
    int state,
    int action,
    double reward,
    int next_state,
    int done
);

int is_snake_position(
    int x,
    int y
);

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

void reset_game(
    char board[MAX_HEIGHT][MAX_WIDTH],
    int width,
    int height,
    int *food_x,
    int *food_y,
    int *dx,
    int *dy,
    int *score
);

#endif
