# include <stdio.h>
# include "racing_game.h"

static int car_x;
static int road_offset = 0;

void init_game(void)
{
    car_x = WIDTH / 2;
    road_offset = 0;
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