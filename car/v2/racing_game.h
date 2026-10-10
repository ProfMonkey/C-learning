#ifndef RACING_GAME_H
#define RACING_GAME_H

#define WIDTH 30
#define HEIGHT 10


typedef struct
{
    int car_x;
    int car_y;
    int car_status;
    int id;
} Car;

Car cars[4];

typedef struct
{
    int obstacle_x;
    int obstacle_y;
    int obstacle_active;
} Obstacle;

Obstacle obstacles[4];

typedef enum
{
    GAME_RUNNING,
    GAME_OVER,
    GAME_EXIT,
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
