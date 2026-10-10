 #ifndef RACING_GAME_H
#define RACING_GAME_H

#define WIDTH 40
#define HEIGHT 10
#define OBSTACLE_COUNT 4

typedef struct
{
    int car_x;
    int car_y;
} Car;

typedef struct
{
    int obstacle_x;
    int obstacle_y;
    int active;
} Obstacle;

typedef enum
{
    GAME_RUNNING,
    GAME_OVER,
    GAME_EXIT
} GameStatus;

void init_game(Car *car);
void move_car(Car *car, int key);
void draw_track(Car *car);
void free_game(void);

#endif