typedef struct
{
    int car_x;
    int car_y;
    int car_status;
} Car;

Car car[4];

typedef struct
{
    int obstacle_x;
    int obstacle_y;
    int obstacle_active;
} Obstacle;

Obstacle obstacle[8];

typedef enum
{
    GAME_RUNNING,
    GAME_OVER,
    GAME_EXIT,
} Gamestatus;

Gamestatus game_status;


void init_game(void);
void move_car(int key);
void draw_track(void);
int change_player(void);
int init_player(void);