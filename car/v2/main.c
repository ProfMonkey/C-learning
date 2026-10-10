#include "racing_game.h"
#include <stdio.h>

int main(void)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD top_left = {0, 0};
    int player = change_player();

    if (game_status != GAME_EXIT)
    {

        if (_kbhit())
            {
                int key = _getch();
                if (key == 'q' || key == 'Q')
                {
                    game_status = GAME_OVER;
                    return 0;
                }
                move_car(key);
            }
        if (game_status != GAME_OVER&& game_status != GAME_EXIT)
        { init_player()++;
        system("cls");
        SetConsoleCursorPosition(console, top_left);
        draw_track();
        }
    }
    return 0;
}