#ifndef ENEMY_STRUCT_H
#define ENEMY_STRUCT_H
#include "raylib.h"
#include "animation_struct.h"
#include "action_struct.h"

typedef struct EnemyActions
{
    Action* enemy_move;
    Action* enemy_attack;
    Action* enemy_die;
}EnemyActions;

typedef struct EnemyAnimationsInfo
{
    Animation anim;
    int size_x;
    int size_y;
    int alignment_x;
    int alignment_y;
    float rotate;
}EnemyAnimationsInfo;
typedef struct EnemyAnimationsEffects
{
    EnemyAnimationsInfo* effect_attack;
}EnemyAnimationsEffects;
typedef struct EnemyCurrentEffects
{
    Animation** current_attack_animation;

}EnemyCurrentEffects;
typedef struct EnemyAnimations
{
    int skin;
    Animation breathe;
    Animation attack;
    Animation walk;
    Animation corpse;
    Animation receiving_damage;
    Animation fall;
    Animation preparation;
    int size_x;
    int size_y;
    int alignment_x;
    int alignment_y;
}EnemyAnimations;
typedef struct EnemyMisc
{
    Vector2 next_move;
    bool activated;
    int path_len;
}EnemyMisc;
typedef struct EnemyPixelsPos
{
    Vector2 pos_pixels;

}EnemyPixelsPos;

typedef struct EnemyTilesPos
{
    Vector2 pos_tiles;

}EnemyTilesPos;
typedef struct EnemyPos
{
    EnemyTilesPos* position_tiles;
    EnemyPixelsPos* position_pixels;


}EnemyPos;
typedef struct EnemyStamina
{
    int max_stamina;
    int stamina;
    int stamina_regeneration;
    
}EnemyStamina;
typedef struct EnemyCharacteristics
{
    EnemyStamina* enemy_stamina;
    int heal_points;
    int defense;
    int max_physical_damage;
    int min_physical_damage;
    int fast_max_physical_damage;
    int fast_min_physical_damage;
}EnemyCharacteristics;
typedef struct EnemyStats
{
    int max_timer;
    int current_timer;
}EnemyStats;
typedef struct EnemyMain
{
    EnemyStats* enemy_stats;
    char* name;
    int index;
    int live;
}EnemyMain;
typedef struct Enemy
{
    EnemyMain* enemy_main;
    EnemyCharacteristics* enemy_characteristics;
    EnemyPos* enemy_position;
    EnemyMisc* enemy_misc;
    EnemyAnimations* enemy_animations;
    EnemyAnimationsEffects* enemy_animations_effects;
    EnemyCurrentEffects* enemy_current_effects;
    Animation** current_animation;
}Enemy;
#endif