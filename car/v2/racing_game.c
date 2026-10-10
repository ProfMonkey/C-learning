#include "racing_game.h"

static Car cars[4];
static Obstacle obstacles[4];

#define WIDTH 40
#define HEIGHT 10

static int current_player = 0;
char board[WIDTH][HEIGHT];

for (int x = 0; x < WIDTH; x++)
{
    for (int y = 0; y < HEIGHT; y++)
    {
        board[x][y] = ' ';
    }
}

for (int x = 0; x < WIDTH; x++)
{
    for (int y = 0; y < HEIGHT; y++)
    {
        if (x == 0 || x == WIDTH-1 || y == 0 || y == HEIGHT-1)
        {
            board[x][y] = '#';
        }
    }
}

void init_game()
{
    int car[x].car_x = WIDTH /2;
    int car[x].car_y = 0;
    for (int x = 0; x < 4; x++)
    {
        car[x].car_status = 0;
        board[car[x].car_x][car[x].car_y] = ' ';
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

int change_player()
{
    current_player = (current_player + 1) % 4;
    return current_player;
}

int init_player()
{
    cars[current_player].car_x = WIDTH / 2;
    cars[current_player].car_y = 0;
    board[cars[current_player].car_x][cars[current_player].car_y] = 'A';
    return board[cars[current_player].car_x][cars[current_player].car_y];
}

void draw_track()
{
    for (int y = 0; y < HEIGHT ; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            board[y][x]='#';
            printf("%c", board[x][y]);
        }
    }
}