#include <windows.h>
#include <conio.h>
#include "racing_game.h"
#include <stdio.h>

int main(void)
{
    Obstacle *obstacles = NULL;
    Obstacle *temp;
    Car car;
    GameStatus status = GAME_RUNNING;
    int obstacle_count = 4;

    obstacles = malloc(obstacle_count * sizeof(Obstacle));
    if (obstacles == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for obstacles.\n");
        return 1;
    }
    obstacle_count = 8;
    temp = realloc(obstacles, obstacle_count * sizeof(Obstacle));
    if (temp != NULL)
    {
        obstacles = temp;
    }
    else 
    {
        fprintf(stderr, "Failed to reallocate memory for obstacles.\n");
        free(obstacles);
        return 1;
    }

    for (int i = 0; i < obstacle_count; i++)
    {
        obstacles[i].obstacle_x = 0;
        obstacles[i].obstacle_y = 0;
        obstacles[i].active = 0;
    }

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD top_left = {0, 0};

    init_game(&car);

    while (status == GAME_RUNNING)
    {
        if (_kbhit())
        {
            int key = _getch();

            if (key == 'q' || key == 'Q')
            {
                status = GAME_EXIT;
                break;
            }

            move_car(&car, key);
        }

        SetConsoleCursorPosition(console, top_left);
        draw_track(&car);
        Sleep(60);
    }
    free(obstacles);
    return 0;
}