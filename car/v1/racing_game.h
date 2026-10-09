# ifndef RACING_GAME_H
# define RACING_GAME_H

#define WIDTH 30
#define HEIGHT 10

void init_game(void);

void draw_track(void);

void move_car(int key);

void update_road(void);

void spawn_obstacle(void);
void update_obstacles(void);

void collision(void);

# endif