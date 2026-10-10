#include <stdio.h>

typedef struct
{
    int id;
    int x;
    int y;
} Car;

typedef struct
{
    int id;
    int x;
    int y;
    int active;
} Obstacle;

typedef struct
{
    int score;
    int distance;
} ScoreData;

typedef enum
{
    GAME_RUNNING,
    GAME_OVER,
    GAME_EXIT,
} GameState;

