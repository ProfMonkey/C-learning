#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "snake_v3_game.h"

int main(void)
{
    char board[MAX_HEIGHT][MAX_WIDTH];
    int width, height;

    printf("Enter width (20-%d): ", MAX_WIDTH);
    scanf("%d", &width);

    printf("Enter height (10-%d): ", MAX_HEIGHT);
    scanf("%d", &height);

    if (width < 20 || width > MAX_WIDTH ||
        height < 10 || height > MAX_HEIGHT)
    {
        printf("Invalid map size.\n");
        return 1;
    }

    srand((unsigned int)time(NULL));

    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            board[y][x] = ' ';

    for (int x = 0; x < width; x++)
    {
        board[0][x] = '#';
        board[height - 1][x] = '#';
    }

    for (int y = 0; y < height; y++)
    {
        board[y][0] = '#';
        board[y][width - 1] = '#';
    }

    snake_x[0] = width / 2;
    snake_y[0] = height / 2;

    for (int i = 1; i < snake_length; i++)
    {
        snake_x[i] = snake_x[0] - i;
        snake_y[i] = snake_y[0];
    }

    for (int i = 0; i < snake_length; i++)
    {
        if (i == 0)
            board[snake_y[i]][snake_x[i]] = '@';
        else
            board[snake_y[i]][snake_x[i]] = '#';
    }

    int food_x, food_y;

    do
    {
        food_x = rand() % (width - 2) + 1;
        food_y = rand() % (height - 2) + 1;
    }
    while (is_snake_position(food_x, food_y));

    board[food_y][food_x] = '*';

    int dx = 1, dy = 0;
    int step = 0;
    int score = 0;

    FILE *debug_file = fopen("debug.txt", "w");

    if (debug_file == NULL)
    {
        printf("debug.txt open failed\n");
        return 1;
    }

    printf("\x1b[2J\x1b[H");
    printf("\x1b[?25l");

    print_board(board, width, height, score);

    while (1)
    {
        int action = ACTION_STRAIGHT;
        int new_dx, new_dy;

        action_to_direction(
            action,
            dx, dy,
            &new_dx, &new_dy
        );

        dx = new_dx;
        dy = new_dy;

        int old_head_x = snake_x[head_index];
        int old_head_y = snake_y[head_index];

        int new_head_x = old_head_x + dx;
        int new_head_y = old_head_y + dy;

        if (is_safe_move(
            new_head_x, new_head_y,
            food_x, food_y,
            width, height
        ) == 0)
        {
            break;
        }

        move_one_step(
            board, width, height,
            new_head_x, new_head_y,
            &food_x, &food_y, &score
        );

        int new_tail_index =
            (head_index + snake_length - 1) % MAX_SNAKE;

        fprintf(
            debug_file,
            "step=%d head=%d tail=%d head_pos=(%d,%d) direction=(%d,%d) length=%d score=%d\n",
            step,
            head_index,
            new_tail_index,
            snake_x[head_index],
            snake_y[head_index],
            dx, dy,
            snake_length,
            score
        );

        fflush(debug_file);
        print_board(board, width, height, score);

        step++;
    }

    fclose(debug_file);

    printf("\x1b[?25h");
    printf("\nGame over.\n");
    printf("Final score: %d\n", score);

    return 0;
}
