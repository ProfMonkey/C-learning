# include <stdio.h>
# include "racing_game.h"
#include <stdlib.h>
#include <time.h>

#define MAX_OBSTACLES 5

static int obstacle_x[MAX_OBSTACLES];
static int obstacle_y[MAX_OBSTACLES];
static int obstacle_active[MAX_OBSTACLES];
static int car_x;
static int road_offset = 0;

void init_game(void)
{
    car_x = WIDTH / 2;
    road_offset = 0;
for (int i = 0; i < MAX_OBSTACLES; i++)
{
    obstacle_active[i] = 0;
}
}

void draw_track(void)
{
    char board[HEIGHT][WIDTH];
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            board[i][j] = ' ';
        }
    }

    for (int i = 0; i < HEIGHT; i++)
    {
        board[i][0] = '#';
        board[i][WIDTH - 1] = '#';
    }

    for (int j =0; j < WIDTH; j++)
    {
        board[0][j] = '#';
        board[HEIGHT - 1][j] = '#';
    }

   for (int y = 1; y < HEIGHT - 1; y++)
   {
      if ((y - road_offset + 4) % 4 < 2)
      {
        board[y][WIDTH / 3] = '|';
        board[y][WIDTH * 2 / 3] = '|';
      }
    }

    for (int i = 0; i < MAX_OBSTACLES; i++)
{
    if (obstacle_active[i] == 1)
    {
        int x = obstacle_x[i];
        int y = obstacle_y[i];
        if (y > 0 && y < HEIGHT - 1 && x > 0 && x < WIDTH - 1)
        {
            board[y][x] = 'X';
        }
    }
}

    board[HEIGHT - 2][car_x] = 'A';
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }

}

 void move_car(int key)
    {
        if((key == 'a' || key == 'A')&&car_x > 1)
        {
            car_x--;
        }
        if((key == 'd' || key == 'D')&&car_x < WIDTH - 2)
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
    int lane_x[3]={WIDTH / 6,WIDTH / 2,WIDTH / 1.2};
    for (int i = 0; i < MAX_OBSTACLES; i++)
    {
        if (obstacle_active[i] == 0)
        {
            int lane = rand() % 3;

            obstacle_x[i] = lane_x[lane];
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
        if (obstacle_active[i] == 1)
        {
            obstacle_y[i]++;
            if (obstacle_y[i] >= HEIGHT - 1)
            {
                obstacle_active[i] = 0;
            }
        }
    }
}

int collision(void)
{
    for (int i = 0; i < MAX_OBSTACLES; i++)
    {
        if (obstacle_active[i] == 1)
        {
            int x = obstacle_x[i];
            int y = obstacle_y[i];
            if (y == HEIGHT - 2 && x == car_x)
            {
                return 1;
            }
        }
    }
    return 0;
}


