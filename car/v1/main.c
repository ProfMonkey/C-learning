
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

    // 外层循环：控制整个游戏程序
    while (!quit_game)
    {
        system("cls");
        init_game();

        int frame = 0;
        int game_over = 0;

        // 内层循环：运行一局赛车
        while (!game_over && !quit_game)
        {
            // 1. 处理玩家输入
            if (_kbhit())
            {
                int key = _getch();

                if (key == 'q' || key == 'Q')
                {
                    quit_game = 1;
                    break;
                }

                move_car(key);
            }

            // 2. 检查玩家移动后的碰撞
            if (collision() == 1)
            {
                game_over = 1;
            }

            // 3. 更新游戏世界
            if (!game_over)
            {
                frame++;

                int a = 4;
                switch (get_score())
                {
                    case 0  9:
                        a = 4;
                        break;
                    case 10  19:
                        a = 3;
                        break;
                    case 20  29:
                        a = 2;
                        break;
                    default:
                        a = 1;
                        break;
                }

                if (frame % a == 0)
                {
                    update_road();
                    update_obstacles();
                }

                if (frame % 20 == 0)
                {
                    spawn_obstacle();
                }

                // 4. 检查障碍车辆移动后的碰撞
                if (collision() == 1)
                {
                    game_over = 1;
                }
            }

            // 5. 绘制画面
            SetConsoleCursorPosition(console, top_left);

            draw_track();
            printf("Score: %-8d\n", get_score());

            if (!game_over)
            {
                Sleep(60);
            }
        }

        // 玩家主动退出
        if (quit_game)
        {
            break;
        }

        // 一局结束
        printf("Game Over! Final Score: %d\n", get_score());
        printf("Press R to restart, Q to quit.\n");

        // 等待玩家选择
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
    }

    printf("\nGame exited.\n");

    return 0;
}
