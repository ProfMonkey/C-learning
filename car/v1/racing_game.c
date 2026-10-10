#include <stdio.h>
#include <stdlib.h>
#include "racing_game.h"

#define MAX_OBSTACLES 5
#define OBSTACLE_HALF_WIDTH 1  // The obstacle car is 3 characters wide: XXX

static int obstacle_x[MAX_OBSTACLES];
static int obstacle_y[MAX_OBSTACLES];
static int obstacle_active[MAX_OBSTACLES];
static int car_x;
static int road_offset;
static int passed_cars;

void init_game(void)
{
    car_x = WIDTH / 2;
    road_offset = 0;
    passed_cars = 0;

    for (int i = 0; i < MAX_OBSTACLES; i++)
    {
        obstacle_active[i] = 0;
        obstacle_x[i] = 0;
        obstacle_y[i] = 0;
    }
}

void draw_track(void)
{
    char board[HEIGHT][WIDTH];

    // Initialize an empty board.
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            board[y][x] = ' ';
        }
    }

    // Top/bottom and left/right borders.
    for (int y = 0; y < HEIGHT; y++)
    {
        board[y][0] = '#';
        board[y][WIDTH - 1] = '#';
    }
    for (int x = 0; x < WIDTH; x++)
    {
        board[0][x] = '#';
        board[HEIGHT - 1][x] = '#';
    }

    // Moving dashed road markings.
    for (int y = 1; y < HEIGHT - 1; y++)
    {
        if ((y - road_offset + 4) % 4 < 2)
        {
            board[y][WIDTH / 3] = '|';
            board[y][WIDTH * 2 / 3] = '|';
        }
    }

    // Draw all active obstacles with width 3.
    for (int i = 0; i < MAX_OBSTACLES; i++)
    {
        if (!obstacle_active[i])
        {
            continue;
        }

        int x = obstacle_x[i];
        int y = obstacle_y[i];
        if (y > 0 && y < HEIGHT - 1 &&
            x - OBSTACLE_HALF_WIDTH > 0 &&
            x + OBSTACLE_HALF_WIDTH < WIDTH - 1)
        {
            for (int dx = -OBSTACLE_HALF_WIDTH; dx <= OBSTACLE_HALF_WIDTH; dx++)
            {
                board[y][x + dx] = 'X';
            }
        }
    }

    // Render the player last so its position is always visible.
    board[HEIGHT - 2][car_x] = 'A';

    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            putchar(board[y][x]);
        }
        putchar('\n');
    }
}

void move_car(int key)
{
    if ((key == 'a' || key == 'A') && car_x > 1)
    {
        car_x--;
    }
    else if ((key == 'd' || key == 'D') && car_x < WIDTH - 2)
    {
        car_x++;
    }
}

void update_road(void)
{
    road_offset = (road_offset + 1) % 4;
}

void spawn_obstacle(void)
{
    for (int i = 0; i < MAX_OBSTACLES; i++)
    {
        if (!obstacle_active[i])
        {
            // Obstacles occupy x-1, x and x+1.
            // Centers range from 2 to WIDTH-3 (27 when WIDTH=30).
            obstacle_x[i] = 2 + rand() % (WIDTH - 4);
            obstacle_y[i] = 1;
            obstacle_active[i] = 1;
            break;
        }
    }
}

void update_obstacles(void)
{
    for (int i = 0; i < MAX_OBSTACLES; i++)
    {
        if (obstacle_active[i])
        {
            obstacle_y[i]++;
            if (obstacle_y[i] >= HEIGHT - 1)
            {
                obstacle_active[i] = 0;
                passed_cars++;
            }
        }
    }
}

int collision(void)
{
    for (int i = 0; i < MAX_OBSTACLES; i++)
    {
        if (obstacle_active[i] && obstacle_y[i] == HEIGHT - 2)
        {
            int x = obstacle_x[i];
            if (car_x >= x - OBSTACLE_HALF_WIDTH &&
                car_x <= x + OBSTACLE_HALF_WIDTH)
            {
                return 1;
            }
        }
    }
    return 0;
}

int get_score(void)
{
    return passed_cars;
}
