#ifndef MISC_STRUCT_H
#define MISC_STRUCT_H
#include "raylib.h"

typedef struct MonitorSize
{
    int monitor_width;
    int monitor_height;
} MonitorSize;
typedef struct Path
{
    Vector2 **parents_position_tiles;
    char **visited_tiles;

} Path;
typedef struct SpeedAnim
{
    float player_movement;
} SpeedAnim;
typedef struct Misc
{
    Camera2D camera;
    MonitorSize monitor_size;
    Path *path;
    SpeedAnim *speed_anim;
} Misc;
#endif