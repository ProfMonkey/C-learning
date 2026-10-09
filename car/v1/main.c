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
    int game_over = 0;
    int survival_time = 0;

    while (1)
    {
        frame++;
        if (frame % 4 == 0)  
        {
            update_road();
            update_obstacles();
        }
        if(frame % 20 ==0)
        {
            spawn_obstacle();
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
         if (collision() == 1)
    {
        game_over = 1;
        break;
    }
      survival_time++;
    printf("score=%d", car_score()+survival_time);

        Sleep(60);
        
    }

    if (game_over == 1)
{
    printf("\nGame Over!\n");
}
else
{
    printf("\nGame exited.\n");
}

    printf("\nGame exited.\n");

    return 0;
}