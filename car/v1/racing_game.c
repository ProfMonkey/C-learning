# include <stdio.h>
# include "racing_game.h"

void init_game(void)
{
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
            printf("%c", board[i][j]);
        }
        printf("\n");
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
    
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}