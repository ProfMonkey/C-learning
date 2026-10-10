#include <stdio.h>
#include "racing_game.h"

static Car cars[PLAYER_COUNT];
static Obstacle obstacles[OBSTACLE_COUNT];
static int current_player = 0;

void init_game(void)
{  
    current_player = 0;

    for (int i = 0; i < PLAYER_COUNT; i++)
    {cars[i].car_x = WIDTH / 2;
     cars[i].car_y = HEIGHT - 2;
     cars[i].car_status = 0;}

    for (int i = 0; i < OBSTACLE_COUNT; i++)
    {obstacles[i].obstacle_x = 0;
     obstacles[i].obstacle_y = 0;
     obstacles[i].obstacle_active = 0;}
}

static void move_one_car(Car *car, int key)
{
    (void)current_player;
    car->car_x = cars[current_player].car_x;
    car->car_y = cars[current_player].car_y;
    if ((key == 'a' || key == 'A') && car->car_x > 1)
    {car->car_x--;}
    else if ((key == 'd' || key == 'D') && car->car_x < WIDTH - 2)
    {car->car_x++;}
}

void move_car(int key)
{
    Car*p = &cars[current_player];

    move_one_car(p,key);
}



void init_player(void)
{
    cars[current_player].car_x = WIDTH / 2;
    cars[current_player].car_y = HEIGHT - 2;
    cars[current_player].car_status = 0;
}

int change_player(void)
{
    current_player = (current_player + 1) % PLAYER_COUNT;
    return current_player;
}

void draw_track(void)
{
    char board[HEIGHT][WIDTH];

    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            if (y == 0 || y == HEIGHT - 1 ||
                x == 0 || x == WIDTH - 1)
            {
                board[y][x] = '#';
            }
            else
            {
                board[y][x] = ' ';
            }
        }
    }

    board[cars[current_player].car_y]
         [cars[current_player].car_x] = 'A';

    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            putchar(board[y][x]);
        }

        putchar('\n');
    }

    printf("Player %d | A/D: Move | N: Next | Q: Quit    \n",
           current_player + 1);
}
