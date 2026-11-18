#ifndef PLAYER_STRUCT_H
#define PLAYER_STRUCT_H
#include "raylib.h"
#include "animation_struct.h"


typedef struct PlayerCharacteristics
{
    int heal_points;
    int defense;
    int max_physical_damage;
    int min_physical_damage;

}PlayerCharacteristics;
typedef struct PlayerEquipmentTier
{
    int armor_tier;
    int sword_tier;
    int HELMET_tier;

}PlayerEquipmentTier;
typedef struct PlayerExp
{
    int experience_points;

    int level;
}PlayerExp;
typedef struct PlayerCoins
{
    int coins;

}PlayerCoins;

typedef struct PlayerStats
{
    PlayerExp* player_exp;
    PlayerCoins* player_coins;
    PlayerEquipmentTier* player_equipment_tier;
    PlayerCharacteristics* player_characteristics;

}PlayerStats;
typedef struct SwordOffsetPos
{
    Vector2 current_pos;
    Vector2 offset;
    Vector2 alignment;
    float current_rotate;
}SwordOffsetPos;
typedef struct ArmorOffsetPos
{
    Vector2 current_pos;
    Vector2 offset;
    Vector2 alignment;

}ArmorOffsetPos;
typedef struct HelmetOffsetPos
{
    Vector2 current_pos;
    Vector2 offset;
    Vector2 alignment;

}HelmetOffsetPos;
typedef struct PlayerEquipmentOffsetPos
{
    ArmorOffsetPos* armor_pos;
    HelmetOffsetPos* helmet_pos;
    SwordOffsetPos* sword_pos;
    

}PlayerEquipmentOffsetPos;
typedef struct HeadOffsetPos
{
    Vector2 current_pos;
    Vector2 offset;
    Vector2 alignment;

}HeadOffsetPos;
typedef struct PlayerPixelsPos
{
    Vector2 pos_pixels;

}PlayerPixelsPos;
typedef struct PlayerTilesPos
{
    Vector2 pos_tiles;

}PlayerTilesPos;
typedef struct PlayerPos
{
    PlayerTilesPos* position_tiles;
    PlayerPixelsPos* position_pixels;
    HeadOffsetPos* head_pos;
    PlayerEquipmentOffsetPos* equipment_pos;

}PlayerPos;
typedef struct PlayerCurrentEquipmentAnimations
{
    Animation** current_armor_anim;
    Animation** current_sword_anim;
    Animation** current_helmet_anim;
    
}PlayerCurrentEquipmentAnimations;
typedef struct PlayerCurrentAnimations
{
    Animation** current_anim;
    Animation** current_head_anim;
    PlayerCurrentEquipmentAnimations* current_equipment_anim;
}PlayerCurrentAnimations;
typedef struct PlayerHeadAnimations
{
    Animation ordinary_head_animation;
    Animation angry_head_animation;
    Animation weak_head_animation;
    int size_x;
    int size_y;
    int alignment_x;
    int alignment_y;
}PlayerHeadAnimations;
typedef struct PlayerActionAnimations
{
    Animation player_breathe_animation;
    Animation player_walk_animation;
    Animation player_attack_animation;
    Animation player_die_animation;
    Animation player_mine_animation;
    int size_x;
    int size_y;
    int alignment_x;
    int alignment_y;
    
}PlayerActionAnimations;
typedef struct PlayerEquipmentAnimations
{
    Animation armor_animation;
    Animation sword_animation;
    Animation helmet_animation;
    
}PlayerEquipmentAnimations;
typedef struct PlayerAnimations
{
    PlayerEquipmentAnimations* player_equipment_animation;
    PlayerActionAnimations*player_action_animation;
    PlayerHeadAnimations* player_head_animation;
}PlayerAnimations;
typedef struct Player
{
    PlayerStats* player_stats;
    PlayerPos* player_pos;
    PlayerCurrentAnimations* current_animations;
    PlayerAnimations* player_anim;
}Player;
#endif