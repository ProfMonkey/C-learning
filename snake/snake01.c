#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define MAX_WIDTH 100
#define MAX_HEIGHT 40
#define MAX_SNAKE 4000

int snake_length = 4;
int head_index = 0;

int snake_x[MAX_SNAKE];
int snake_y[MAX_SNAKE];

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
            printf("%c", board[y][x]);
        }

        printf("\n");
    }

    printf("\nWASD move, Q quit\n");
    printf("Score: %d\n", score);

    fflush(stdout);
}

int main(void)
{
    char board[MAX_HEIGHT][MAX_WIDTH];

    int width;
    int height;

    printf(
        "Enter width (20-%d): ",
        MAX_WIDTH
    );

    scanf("%d", &width);

    printf(
        "Enter height (10-%d): ",
        MAX_HEIGHT
    );

    scanf("%d", &height);

    if (
        width < 20 ||
        width > MAX_WIDTH ||
        height < 10 ||
        height > MAX_HEIGHT
    )
    {
        printf("Invalid map size.\n");
        return 1;
    }

    srand((unsigned int)time(NULL));

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            board[y][x] = ' ';
        }
    }

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
        snake_x[i] =
            snake_x[0] - i;

        snake_y[i] =
            snake_y[0];
    }

    for (int i = 0; i < snake_length; i++)
    {
        if (i == 0)
        {
            board
                [snake_y[i]]
                [snake_x[i]]
                = '@';
        }
        else
        {
            board
                [snake_y[i]]
                [snake_x[i]]
                = '#';
        }
    }

    int food_x;
    int food_y;

    do
    {
        food_x =
            rand() % (width - 2) + 1;

        food_y =
            rand() % (height - 2) + 1;
    }
    while (
        is_snake_position(
            food_x,
            food_y
        )
    );

    board[food_y][food_x] = '*';

    int dx = 0;
    int dy = 0;

    int step = 0;
    int score = 0;

    FILE* debug_file =
        fopen("debug.txt", "w");

    if (debug_file == NULL)
    {
        printf("debug.txt open failed\n");
        return 1;
    }

    printf("\x1b[2J\x1b[H");
    printf("\x1b[?25l");

    print_board(
        board,
        width,
        height,
        score
    );

    while (1)
    {
        char key = _getch();

        fprintf(
            debug_file,
            "KEY: %c code=%d\n",
            key,
            (unsigned char)key
        );

        fflush(debug_file);

        int should_move = 0;

        if (
            (key == 'w' || key == 'W') &&
            dy != 1
        )
        {
            dx = 0;
            dy = -1;
            should_move = 1;
        }
        else if (
            (key == 's' || key == 'S') &&
            dy != -1
        )
        {
            dx = 0;
            dy = 1;
            should_move = 1;
        }
        else if (
            (key == 'a' || key == 'A') &&
            dx != 1
        )
        {
            dx = -1;
            dy = 0;
            should_move = 1;
        }
        else if (
            (key == 'd' || key == 'D') &&
            dx != -1
        )
        {
            dx = 1;
            dy = 0;
            should_move = 1;
        }
        else if (
            key == 'q' ||
            key == 'Q'
        )
        {
            break;
        }

        if (should_move == 0)
        {
            continue;
        }

        int old_head_x =
            snake_x[head_index];

        int old_head_y =
            snake_y[head_index];

        int new_head_x =
            old_head_x + dx;

        int new_head_y =
            old_head_y + dy;

        if (
            new_head_x <= 0 ||
            new_head_x >= width - 1 ||
            new_head_y <= 0 ||
            new_head_y >= height - 1
        )
        {
            break;
        }

        int ate_food;

        if (
            new_head_x == food_x &&
            new_head_y == food_y
        )
        {
            ate_food = 1;
        }
        else
        {
            ate_food = 0;
        }

        int tail_index =
            (
                head_index +
                snake_length -
                1
            )
            % MAX_SNAKE;

        if (
            !(
                new_head_x ==
                    snake_x[tail_index] &&
                new_head_y ==
                    snake_y[tail_index] &&
                ate_food == 0
            )
        )
        {
            if (
                is_snake_position(
                    new_head_x,
                    new_head_y
                )
            )
            {
                break;
            }
        }

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
            score += 10;

            do
            {
                food_x =
                    rand() % (width - 2) + 1;

                food_y =
                    rand() % (height - 2) + 1;
            }
            while (
                is_snake_position(
                    food_x,
                    food_y
                )
            );

            board[food_y][food_x] = '*';
        }

        int new_tail_index =
            (
                head_index +
                snake_length -
                1
            )
            % MAX_SNAKE;

        fprintf(
            debug_file,
            "step=%d head=%d tail=%d head_pos=(%d,%d) direction=(%d,%d) length=%d score=%d\n",
            step,
            head_index,
            new_tail_index,
            snake_x[head_index],
            snake_y[head_index],
            dx,
            dy,
            snake_length,
            score
        );

        fflush(debug_file);

        print_board(
            board,
            width,
            height,
            score
        );

        step++;
    }

    fclose(debug_file);

    printf("\x1b[?25h");

    printf("\nGame over.\n");
    printf("Final score: %d\n", score);

    return 0;
}
