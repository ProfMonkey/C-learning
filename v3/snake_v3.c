#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "snake_v3_game.h"

int main(void)
{
    char board[MAX_HEIGHT][MAX_WIDTH];

    int width, height;

    printf("Enter width (20-%d): ", MAX_WIDTH);
    scanf("%d", &width);

    printf("Enter height (10-%d): ", MAX_HEIGHT);
    scanf("%d", &height);

    if (width < 20 || width > MAX_WIDTH ||
        height < 10 || height > MAX_HEIGHT)
    {
        printf("Invalid map size.\n");
        return 1;
    }

    srand((unsigned int)time(NULL));

    FILE *debug_file = fopen("debug.txt", "w");

    if (debug_file == NULL)
    {
        printf("debug.txt open failed\n");
        return 1;
    }

    printf("\x1b[2J\x1b[H");
    printf("\x1b[?25l");

    int food_x, food_y;
    int dx, dy;
    int score;
    int step;

    for (int episode = 0; episode < 10000; episode++)
    {
        step = 0;

        reset_game(
            board,
            width,
            height,
            &food_x,
            &food_y,
            &dx,
            &dy,
            &score
        );

        int state = get_state(
            dx, dy,
            food_x, food_y,
            width, height
        );

        print_board(
            board,
            width,
            height,
            score
        );

        while (1)
        {
            int action = choose_action(state, 0.1);

            int new_dx;
            int new_dy;

            action_to_direction(
                action,
                dx, dy,
                &new_dx, &new_dy
            );

            dx = new_dx;
            dy = new_dy;

            int old_head_x = snake_x[head_index];
            int old_head_y = snake_y[head_index];

            int new_head_x = old_head_x + dx;
            int new_head_y = old_head_y + dy;

            int ate_food =
                new_head_x == food_x &&
                new_head_y == food_y;

            if (is_safe_move(
                new_head_x,
                new_head_y,
                food_x,
                food_y,
                width,
                height
            ) == 0)
            {
                double reward = calculate_reward(
                    1,
                    0
                );

                update_q_value(
                    state,
                    action,
                    reward,
                    0,
                    1
                );

                break;
            }

            move_one_step(
                board,
                width,
                height,
                new_head_x,
                new_head_y,
                &food_x,
                &food_y,
                &score
            );

            double reward = calculate_reward(
                0,
                ate_food
            );

            int new_state = get_state(
                dx, dy,
                food_x, food_y,
                width, height
            );

            update_q_value(
                state,
                action,
                reward,
                new_state,
                0
            );

            state = new_state;

            int new_tail_index =
                (head_index + snake_length - 1)
                % MAX_SNAKE;

            fprintf(
                debug_file,
                "episode=%d step=%d state=%d head=%d tail=%d "
                "head_pos=(%d,%d) direction=(%d,%d) "
                "length=%d score=%d\n",
                episode + 1,
                step,
                state,
                head_index,
                new_tail_index,
                snake_x[head_index],
                snake_y[head_index],
                dx,
                dy,
                snake_length,
                score
            );

            fflush(debug_file);

            print_board(
                board,
                width,
                height,
                score
            );

            step++;
        }
    }

    fclose(debug_file);

    printf("\x1b[?25h");
    printf("\nTraining finished.\n");

    return 0;
}
