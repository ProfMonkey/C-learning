#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "snake_v2_game.h"

int snake_length = 4;
int head_index = 0;

int snake_x[MAX_SNAKE];
int snake_y[MAX_SNAKE];

int choose_rule_bot_direction(
    int *dx,
    int *dy,
    int food_x,
    int food_y,
    int width,
    int height
)
{
    int forward_dx = *dx;
    int forward_dy = *dy;

    int left_dx;
    int left_dy;

    int right_dx;
    int right_dy;

    get_left_direction(*dx,*dy,&left_dx,&left_dy);
    get_right_direction(*dx,*dy,&right_dx,&right_dy);

    int head_x =
    snake_x[head_index];

    int head_y =
    snake_y[head_index];

    int forward_x =
    head_x + forward_dx;

    int forward_y =
    head_y + forward_dy;

    int left_x =
    head_x + left_dx;

    int left_y =
    head_y + left_dy;

    int right_x =
    head_x + right_dx;

    int right_y =
    head_y + right_dy;

    int forward_safe;
    int left_safe;
    int right_safe;

    forward_safe =
    is_safe_move(
        forward_x,
        forward_y,
        food_x,
        food_y,
        width,
        height
    );

    left_safe =
    is_safe_move(
        left_x,
        left_y,
        food_x,
        food_y,
        width,
        height
    );

    right_safe =
    is_safe_move(
        right_x,
        right_y,
        food_x,
        food_y,
        width,
        height
    );

    if (forward_safe == 1)
    {
        *dx = forward_dx;
        *dy = forward_dy;
        return 1;
    }
    else if (left_safe == 1)
    {
        *dx = left_dx;
        *dy = left_dy;
        return 1;
    }
    else if (right_safe == 1)
    {
        *dx = right_dx;
        *dy = right_dy;
        return 1;
    }
    else
    {
        return -1;
    }
}

void get_left_direction(
    int dx,
    int dy,
    int *new_dx,
    int *new_dy
)
{
    *new_dx = dy;
    *new_dy = -dx;
}

void get_right_direction(
    int dx,
    int dy,
    int *new_dx,
    int *new_dy
)
{
    *new_dx = -dy;
    *new_dy = dx;
}

int is_snake_position(int x, int y)
{
    for (int i = 0; i < snake_length; i++)
    {
        int index =
            (head_index + i) % MAX_SNAKE;

        if (
            snake_x[index] == x &&
            snake_y[index] == y
        )
        {
            return 1;
        }
    }

    return 0;
}

int get_human_direction(
    int *dx,
    int *dy
)
{
    char key = _getch();

    switch (key)
    {
    case 'w':
    case 'W':
        if (*dy != 1)
        {
            *dx = 0;
            *dy = -1;
            return 1;
        }

        return 0;

    case 's':
    case 'S':
        if (*dy != -1)
        {
            *dx = 0;
            *dy = 1;
            return 1;
        }

        return 0;

    case 'a':
    case 'A':
        if (*dx != 1)
        {
            *dx = -1;
            *dy = 0;
            return 1;
        }

        return 0;

    case 'd':
    case 'D':
        if (*dx != -1)
        {
            *dx = 1;
            *dy = 0;
            return 1;
        }

        return 0;

    case 'q':
    case 'Q':
        return -1;

    default:
        return 0;
    }
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
    if (
        new_head_x <= 0 ||
        new_head_x >= width - 1 ||
        new_head_y <= 0 ||
        new_head_y >= height - 1
    )
    {
        return 0;
    }

    int ate_food =
        (
            new_head_x == food_x &&
            new_head_y == food_y
        );

    int tail_index =
        (
            head_index +
            snake_length -
            1
        )
        % MAX_SNAKE;

    if (
        new_head_x == snake_x[tail_index] &&
        new_head_y == snake_y[tail_index] &&
        ate_food == 0
    )
    {
        return 1;
    }

    if (
        is_snake_position(
            new_head_x,
            new_head_y
        )
    )
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
        (
            new_head_x == *food_x &&
            new_head_y == *food_y
        );

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
            [snake_x[tail_index]]
            = ' ';
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

    board
        [old_head_y]
        [old_head_x]
        = '#';

    board
        [new_head_y]
        [new_head_x]
        = '@';

    if (ate_food == 1)
    {
        snake_length++;

        *score += 10;

        do
        {
            *food_x =
                rand() % (width - 2) + 1;

            *food_y =
                rand() % (height - 2) + 1;
        }
        while (
            is_snake_position(
                *food_x,
                *food_y
            )
        );

        board
            [*food_y]
            [*food_x]
            = '*';
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

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            printf(
                "%c",
                board[y][x]
            );
        }

        printf("\n");
    }

    printf(
        "\nWASD move, Q quit\n"
    );

    printf(
        "Score: %d\n",
        score
    );

    fflush(stdout);
}

