#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "racing_game.h"

int main(void)
{
    srand((unsigned int)time(NULL));

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD top_left = {0, 0};
    GameStatus game_status = GAME_RUNNING;

    // Outer loop: start a fresh round after R is pressed.
    while (game_status != GAME_EXIT)
    {
        system("cls");
        init_game();

        int frame = 0;
        int game_over = 0;
        int move_interval = 4;

        while (game_status != GAME_OVER && game_status != GAME_EXIT)
        {
            // 1. Read input without blocking the game loop.
            if (_kbhit())
            {
                int key = _getch();
                if (key == 'q' || key == 'Q')
                {
                    game_status = GAME_EXIT;
                    break;
                }
                move_car(key);
            }

            // 2. Collision immediately after player movement.
            if (collision())
            {
                game_over = 1;
            }

            if (!game_over)
            {
                frame++;

                // 3. Increase difficulty every 10 points.
                switch (get_score() / 10)
                {
                    case 0:
                        move_interval = 4;
                        break;
                    case 1:
                        move_interval = 3;
                        break;
                    case 2:
                        move_interval = 2;
                        break;
                    default:
                        move_interval = 1;
                        break;
                }

                if (frame % move_interval == 0)
                {
                    update_road();
                    update_obstacles();
                }

                // Keep the spacing around 5 movement steps per obstacle.
                int spawn_interval = move_interval * 5;
                if (frame % spawn_interval == 0)
                {
                    spawn_obstacle();
                }

                // 4. Collision after obstacle movement.
                if (collision())
                {
                    game_over = 1;
                }
            }

            // 5. Render the current state.
            SetConsoleCursorPosition(console, top_left);
            draw_track();
            printf("Score: %-8d Speed: %d   \n", get_score(), 5 - move_interval);

            if (!game_over)
            {
                Sleep(60);
            }
        }

        if (game_status == GAME_EXIT)
        {
            break;
        }

        printf("Game Over! Final Score: %d\n", get_score());
        printf("Press R to restart, Q to quit.\n");

        while (1)
        {
            int key = _getch();
            if (key == 'r' || key == 'R')
            {
                break;
            }
            if (key == 'q' || key == 'Q')
            {
                game_status = GAME_EXIT;
                break;
            }
        }
    }

    printf("\nGame exited.\n");
    return 0;
}
