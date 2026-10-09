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
    int quit_game = 0;

    while (!quit_game)
    {
        system("cls");
        init_game();
        int frame = 0;
        int game_over = 0;
        int score= 0;

        while (!game_over && !quit_game)
        {
        if (_kbhit())
        {
            int key = _getch();

            if (key == 'q'||key == 'Q')
            {
                break;
            }

            move_car(key);
        }
         if (collision() == 1)
    {
        game_over = 1;
        break;
    }
     if (!game_over && frame % 4 == 0)
                {
                    score++;
                }
            }

            // 4. 绘制画面及分数
            SetConsoleCursorPosition(console, top_left);
            draw_track();
            printf("Score: %-8d\n", score);

            if (!game_over)
            {
                Sleep(60);
            }
        }

        if (quit_game)
        {
            break;
        }

        // 5. 本局游戏结束
        printf("Game Over! Final Score: %d\n", score);
        printf("Press R to restart, Q to quit.\n");

        // 6. 等待重新开始或者退出
        while (1)
        {
            int key = _getch();

            if (key == 'r' || key == 'R')
            {
                break;
            }

            if (key == 'q' || key == 'Q')
            {
                quit_game = 1;
                break;
            }
        }
    

    printf("\nGame exited.\n");

    return 0;
       
}
    
    