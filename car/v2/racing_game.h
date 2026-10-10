#ifndef RACING_GAME_H
#define RACING_GAME_H

#define WIDTH 30
#define HEIGHT 10


typedef struct
{
    int car_x[WIDTH];
    int car_ststus[1];-
    int id[4];
} Car;

typedef struct
{
    int obstacle_x[WIDTH];
    int obstacle_y[HEIGHT];
    int obstacle_active[1];
} Obstacle;

typedef enum
{
    GAME_RUNNING,
    GAME_OVER,
    GAME_PAUSED
} GameStatus;
  

void init_game(void);
void draw_track(void);
void move_car(int key);
void update_road(void);
void spawn_obstacle(void);
void update_obstacles(void);
int collision(void);
int get_score(void);

#endif
