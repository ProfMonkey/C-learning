#include <windows.h>
#include <conio.h>
#include "racing_game.h"
#include <stdio.h>

int main(void)
{
    Obstacle *obstacles = NULL;
    Car car;
    GameStatus status = GAME_RUNNING;

    obstacles = malloc(4* sizeof(Obstacle));
    if (obstacles == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for obstacles.\n");
        return 1;
    }
    for (int i = 0; i < OBSTACLE_COUNT; i++)
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
    free_game();
    return 0;
}