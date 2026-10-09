#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "racing_game.h"

int main(void)
{
    init_game();

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD top_left = {0, 0};

    int frame = 0;

    while (1)
    {
        frame++;

        if (frame % 4 == 0)  
        {
            update_road();
        }

        if (_kbhit())
        {
            int key = _getch();

            if (key == 'q'||key == 'Q')
            {
                break;
            }

            move_car(key);
        }

        SetConsoleCursorPosition(console, top_left);
        draw_track();

        Sleep(60);
    }

    printf("\nGame exited.\n");

    return 0;
}