#include <stdio.h>
#include "racing_game.h"

void init_game(Car *car)
{
    car->car_x = WIDTH / 2;
    car->car_y = HEIGHT - 2;
}

void move_car(Car *car, int key)
{
    if ((key == 'a' || key == 'A') && car->car_x > 1)
    {
        car->car_x--;
    }
    else if ((key == 'd' || key == 'D') && car->car_x < WIDTH - 2)
    {
        car->car_x++;
    }
}

void draw_track(Car *car)
{
    char board[HEIGHT][WIDTH];

    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            if (y == 0 || y == HEIGHT - 1 || x == 0 || x == WIDTH - 1)
            {
                board[y][x] = '#';
            }
            else
            {
                board[y][x] = ' ';
            }
        }
    }

    board[car->car_y][car->car_x] = 'A';

    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            putchar(board[y][x]);
        }
        putchar('\n');
    }

    printf("A/D: Move | Q: Quit       \n");
}