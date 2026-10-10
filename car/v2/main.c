#include <windows.h>
#include <conio.h>
#include "racing_game.h"

int main(void)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD top_left = {0, 0};

    GameStatus game_status = GAME_RUNNING;

    init_game();

    test_pointer();

    while (game_status == GAME_RUNNING)
    {
        if (_kbhit())
        {
            int key = _getch();

            if (key == 'q' || key == 'Q')
            {
                game_status = GAME_EXIT;
                break;
            }

            if (key == 'n' || key == 'N')
            {
                change_player();
                init_player();
            }
            else
            {
                move_car(key);
            }
        }

        SetConsoleCursorPosition(console, top_left);
        draw_track();

        Sleep(60);
    }

    return 0;
}