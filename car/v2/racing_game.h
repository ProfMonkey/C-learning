#ifndef RACING_GAME_H
#define RACING_GAME_H

#define WIDTH 40
#define HEIGHT 10
#define PLAYER_COUNT 4
#define OBSTACLE_COUNT 4

typedef struct
{
    int car_x;
    int car_y;
    int car_status;
} Car;

typedef struct
{
    int obstacle_x;
    int obstacle_y;
    int obstacle_active;
} Obstacle;

typedef enum
{
    GAME_RUNNING,
    GAME_OVER,
    GAME_EXIT,
} GameStatus;

void init_game(void);
void move_car(int key);
void draw_track(void);
int change_player(void);
void init_player(void);

#endif 