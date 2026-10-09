# include <stdio.h>
# include "racing_game.h"

static int car_x;

void init_game(void)
{
    car_x = WIDTH / 2;

    printf("Game initialized!\n");
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
        int key = _getch();
        if((key == 'a' || key == 'A')&&car_x > 1)
        {
            car_x--;
        }
        if((key == 'd' || key == 'D')&&car_x < WIDTH - 2)
        {
            car_x++;
        }
    }