#include <stdio.h>
#include <stdlib.h>

#include "snake_v3_game.h"

int snake_length = 4;
int head_index = 0;

int snake_x[MAX_SNAKE];
int snake_y[MAX_SNAKE];

double q_table[STATE_COUNT][ACTION_COUNT];

void action_to_direction(
    int action,
    int old_dx, int old_dy,
    int *new_dx, int *new_dy
)
{
    if (action == ACTION_STRAIGHT)
    {
        *new_dx = old_dx;
        *new_dy = old_dy;
    }
    else if (action == ACTION_LEFT)
    {
        get_left_direction(
            old_dx,
            old_dy,
            new_dx,
            new_dy
        );
    }
    else if (action == ACTION_RIGHT)
    {
        get_right_direction(
            old_dx,
            old_dy,
            new_dx,
            new_dy
        );
    }
}

void get_left_direction(
    int dx, int dy,
    int *new_dx, int *new_dy
)
{
    *new_dx = dy;
    *new_dy = -dx;
}

void get_right_direction(
    int dx, int dy,
    int *new_dx, int *new_dy
)
{
    *new_dx = -dy;
    *new_dy = dx;
}

int is_action_safe(
    int action,
    int dx, int dy,
    int food_x, int food_y,
    int width, int height
)
{
    int new_dx;
    int new_dy;

    action_to_direction(
        action,
        dx, dy,
        &new_dx, &new_dy
    );

    int new_head_x =
        snake_x[head_index] + new_dx;

    int new_head_y =
        snake_y[head_index] + new_dy;

    return is_safe_move(
        new_head_x,
        new_head_y,
        food_x,
        food_y,
        width,
        height
    );
}

void get_danger_info(
    int dx, int dy,
    int food_x, int food_y,
    int width, int height,
    int *danger_straight,
    int *danger_left,
    int *danger_right
)
{
    *danger_straight =
        !is_action_safe(
            ACTION_STRAIGHT,
            dx, dy,
            food_x, food_y,
            width, height
        );

    *danger_left =
        !is_action_safe(
            ACTION_LEFT,
            dx, dy,
            food_x, food_y,
            width, height
        );

    *danger_right =
        !is_action_safe(
            ACTION_RIGHT,
            dx, dy,
            food_x, food_y,
            width, height
        );
}

int encode_danger_state(
    int danger_straight,
    int danger_left,
    int danger_right
)
{
    int state =
        danger_straight * 1 +
        danger_left * 2 +
        danger_right * 4;

    return state;
}

void get_food_info(
    int dx, int dy,
    int food_x, int food_y,
    int *food_straight,
    int *food_behind,
    int *food_left,
    int *food_right
)
{
    int head_x = snake_x[head_index];
    int head_y = snake_y[head_index];

    *food_straight = 0;
    *food_behind = 0;
    *food_left = 0;
    *food_right = 0;

    if (dx == 1 && dy == 0)
    {
        if (food_x > head_x)
        {
            *food_straight = 1;
        }

        if (food_x < head_x)
        {
            *food_behind = 1;
        }

        if (food_y < head_y)
        {
            *food_left = 1;
        }

        if (food_y > head_y)
        {
            *food_right = 1;
        }
    }
    else if (dx == -1 && dy == 0)
    {
        if (food_x < head_x)
        {
            *food_straight = 1;
        }

        if (food_x > head_x)
        {
            *food_behind = 1;
        }

        if (food_y > head_y)
        {
            *food_left = 1;
        }

        if (food_y < head_y)
        {
            *food_right = 1;
        }
    }
    else if (dx == 0 && dy == 1)
    {
        if (food_y > head_y)
        {
            *food_straight = 1;
        }

        if (food_y < head_y)
        {
            *food_behind = 1;
        }

        if (food_x > head_x)
        {
            *food_left = 1;
        }

        if (food_x < head_x)
        {
            *food_right = 1;
        }
    }
    else if (dx == 0 && dy == -1)
    {
        if (food_y < head_y)
        {
            *food_straight = 1;
        }

        if (food_y > head_y)
        {
            *food_behind = 1;
        }

        if (food_x < head_x)
        {
            *food_left = 1;
        }

        if (food_x > head_x)
        {
            *food_right = 1;
        }
    }
}

int encode_food_state(
    int food_straight,
    int food_behind,
    int food_left,
    int food_right
)
{
    int food_state =
        food_straight * 1 +
        food_behind * 2 +
        food_left * 4 +
        food_right * 8;

    return food_state;
}

int combine_state(
    int danger_state,
    int food_state
)
{
    int final_state =
        danger_state +
        food_state * 8;

    return final_state;
}

int get_state(
    int dx, int dy,
    int food_x, int food_y,
    int width, int height
)
{
    int danger_straight;
    int danger_left;
    int danger_right;

    int food_straight;
    int food_behind;
    int food_left;
    int food_right;

    get_danger_info(
        dx, dy,
        food_x, food_y,
        width, height,
        &danger_straight,
        &danger_left,
        &danger_right
    );

    int danger_state =
        encode_danger_state(
            danger_straight,
            danger_left,
            danger_right
        );

    get_food_info(
        dx, dy,
        food_x, food_y,
        &food_straight,
        &food_behind,
        &food_left,
        &food_right
    );

    int food_state =
        encode_food_state(
            food_straight,
            food_behind,
            food_left,
            food_right
        );

    int final_state =
        combine_state(
            danger_state,
            food_state
        );

    return final_state;
}

int choose_best_action(int state)
{
    int best_action =
        ACTION_STRAIGHT;

    double best_value =
        q_table[state][best_action];

    for (int i = 1;
         i < ACTION_COUNT;
         i++)
    {
        if (q_table[state][i] >
            best_value)
        {
            best_value =
                q_table[state][i];

            best_action = i;
        }
    }

    return best_action;
}

int choose_random_action(void)
{
    return rand() % ACTION_COUNT;
}

int choose_action(
    int state,
    double epsilon
)
{
    double random_value =
        (double)rand() / RAND_MAX;

    if (random_value < epsilon)
    {
        return choose_random_action();
    }
    else
    {
        return choose_best_action(state);
    }
}

double calculate_reward(
    int died,
    int ate_food
)
{
    if (died)
    {
        return REWARD_DEATH;
    }

    if (ate_food)
    {
        return REWARD_FOOD;
    }

    return REWARD_STEP;
}

double get_max_q_value(int state)
{
    double best_value =
        q_table[state][ACTION_STRAIGHT];

    for (int i = 1;
         i < ACTION_COUNT;
         i++)
    {
        if (q_table[state][i] >
            best_value)
        {
            best_value =
                q_table[state][i];
        }
    }

    return best_value;
}

void update_q_value(
    int state,
    int action,
    double reward,
    int next_state,
    int done
)
{
    double old_q =
        q_table[state][action];

    double max_next_q;

    if (done)
    {
        max_next_q = 0.0;
    }
    else
    {
        max_next_q =
            get_max_q_value(
                next_state
            );
    }

    double new_q =
        old_q +
        ALPHA *
        (
            reward +
            GAMMA * max_next_q -
            old_q
        );

    q_table[state][action] =
        new_q;
}

int is_snake_position(
    int x,
    int y
)
{
    for (int i = 0;
         i < snake_length;
         i++)
    {
        int index =
            (head_index + i)
            % MAX_SNAKE;

        if (snake_x[index] == x &&
            snake_y[index] == y)
        {
            return 1;
        }
    }

    return 0;
}

int is_safe_move(
    int new_head_x,
    int new_head_y,
    int food_x,
    int food_y,
    int width,
    int height
)
{
    if (new_head_x <= 0 ||
        new_head_x >= width - 1 ||
        new_head_y <= 0 ||
        new_head_y >= height - 1)
    {
        return 0;
    }

    int ate_food =
        new_head_x == food_x &&
        new_head_y == food_y;

    int tail_index =
        (
            head_index +
            snake_length -
            1
        )
        % MAX_SNAKE;

    if (new_head_x ==
            snake_x[tail_index] &&
        new_head_y ==
            snake_y[tail_index] &&
        ate_food == 0)
    {
        return 1;
    }

    if (is_snake_position(
        new_head_x,
        new_head_y
    ))
    {
        return 0;
    }

    return 1;
}

void move_one_step(
    char board[MAX_HEIGHT][MAX_WIDTH],
    int width,
    int height,
    int new_head_x,
    int new_head_y,
    int *food_x,
    int *food_y,
    int *score
)
{
    int old_head_x =
        snake_x[head_index];

    int old_head_y =
        snake_y[head_index];

    int ate_food =
        new_head_x == *food_x &&
        new_head_y == *food_y;

    int tail_index =
        (
            head_index +
            snake_length -
            1
        )
        % MAX_SNAKE;

    if (ate_food == 0)
    {
        board
            [snake_y[tail_index]]
            [snake_x[tail_index]] = ' ';
    }

    head_index--;

    if (head_index < 0)
    {
        head_index =
            MAX_SNAKE - 1;
    }

    snake_x[head_index] =
        new_head_x;

    snake_y[head_index] =
        new_head_y;

    board[old_head_y][old_head_x] =
        '#';

    board[new_head_y][new_head_x] =
        '@';

    if (ate_food == 1)
    {
        snake_length++;
        *score += 10;

        do
        {
            *food_x =
                rand() %
                (width - 2) + 1;

            *food_y =
                rand() %
                (height - 2) + 1;
        }
        while (
            is_snake_position(
                *food_x,
                *food_y
            )
        );

        board[*food_y][*food_x] =
            '*';
    }
}

void print_board(
    char board[MAX_HEIGHT][MAX_WIDTH],
    int width,
    int height,
    int score
)
{
    printf("\x1b[H");

    for (int y = 0;
         y < height;
         y++)
    {
        for (int x = 0;
             x < width;
             x++)
        {
            printf(
                "%c",
                board[y][x]
            );
        }

        printf("\n");
    }

    printf(
        "\nScore: %d\n",
        score
    );

    fflush(stdout);
}

void reset_game(
    char board[MAX_HEIGHT][MAX_WIDTH],
    int width,
    int height,
    int *food_x,
    int *food_y,
    int *dx,
    int *dy,
    int *score
)
{
    snake_length = 4;
    head_index = 0;

    for (int y = 0;
         y < height;
         y++)
    {
        for (int x = 0;
             x < width;
             x++)
        {
            board[y][x] = ' ';
        }
    }

    for (int x = 0;
         x < width;
         x++)
    {
        board[0][x] = '#';
        board[height - 1][x] = '#';
    }

    for (int y = 0;
         y < height;
         y++)
    {
        board[y][0] = '#';
        board[y][width - 1] = '#';
    }

    int center_x =
        width / 2;

    int center_y =
        height / 2;

    snake_x[head_index] =
        center_x;

    snake_y[head_index] =
        center_y;

    for (int i = 1;
         i < snake_length;
         i++)
    {
        int index =
            (head_index + i)
            % MAX_SNAKE;

        snake_x[index] =
            center_x - i;

        snake_y[index] =
            center_y;
    }

    for (int i = 0;
         i < snake_length;
         i++)
    {
        int index =
            (head_index + i)
            % MAX_SNAKE;

        if (i == 0)
        {
            board
                [snake_y[index]]
                [snake_x[index]] = '@';
        }
        else
        {
            board
                [snake_y[index]]
                [snake_x[index]] = '#';
        }
    }

    do
    {
        *food_x =
            rand() %
            (width - 2) + 1;

        *food_y =
            rand() %
            (height - 2) + 1;
    }
    while (
        is_snake_position(
            *food_x,
            *food_y
        )
    );

    board[*food_y][*food_x] =
        '*';

    *dx = 1;
    *dy = 0;

    *score = 0;
}
