#ifndef ANIMATION_STRUCT_H
#define ANIMATION_STRUCT_H
#include "raylib.h"

typedef struct Animation  
{
    Texture2D texture;
    Rectangle cur_frameRec;
    Rectangle start_frameRec;
    int direction;
    int currentFrame;
    int frameCount;
    int framesCounter;
    float framesSpeed;
    float frameWidth;
    float frameHeight;
    bool isPlaying;
    int index;
}Animation ;
typedef struct GUIAnimation
{
    
}GUIAnimation;
typedef struct HumanAttacksAnimations
{
    Animation jab;
    Animation slash;
}HumanAttacksAnimations;
typedef struct HumanHead0Animations
{
    Animation ordinary;
    Animation angry;
    Animation weak;
}HumanHead0Animations;
typedef struct HumanHeadAnimations
{
    HumanHead0Animations* human_head_0_animations;
    
}HumanHeadAnimations;
typedef struct HumanAnimations
{
    Animation player_breathe_animation;
    Animation player_walk_animation;
    Animation player_attack_animation;
    Animation player_die_animation;
    Animation player_mine_animation;
    
}HumanAnimations;
typedef struct PlayersAnimations
{
    HumanAnimations* human_animations;
    HumanHeadAnimations* human_head_animations;
    HumanAttacksAnimations* human_attacks_animations;
}PlayersAnimations;
typedef struct ArmEnemiesAnimations
{
    Animation arm_0_breathe_animation;
    Animation arm_0_walk_animation;
    Animation arm_0_attack_animation;
    Animation arm_0_corpse_animation;
    Animation arm_0_receiving_damage_animation;
    Animation arm_0_fall_animation;
    Animation arm_1_breathe_animation;
    Animation arm_1_walk_animation;
    Animation arm_1_attack_animation;
    Animation arm_1_corpse_animation;
    Animation arm_1_receiving_damage_animation;
    Animation arm_1_fall_animation;
    Animation arm_1_preparation_animation;
}ArmEnemiesAnimations;
typedef struct SkeletonEnemiesAnimations
{
    Animation skeleton_breathe_animation;
    Animation skeleton_walk_animation;
    Animation skeleton_attack_animation;
    Animation skeleton_corpse_animation;
    Animation skeleton_receiving_damage_animation;
    Animation skeleton_fall_animation;
}SkeletonEnemiesAnimations;
typedef struct ZombieEnemiesAnimations
{
    Animation zombie_breathe_animation;
    Animation zombie_walk_animation;
    Animation zombie_attack_animation;
    Animation zombie_corpse_animation;
    Animation zombie_receiving_damage_animation;
    Animation zombie_fall_animation;
}ZombieEnemiesAnimations;
typedef struct KnightZombieEnemiesAnimations
{
    Animation knight_zombie_breathe_animation;
    Animation knight_zombie_walk_animation;
    Animation knight_zombie_attack_animation;
    Animation knight_zombie_corpse_animation;
    Animation knight_zombie_receiving_damage_animation;
    Animation knight_zombie_fall_animation;
}KnightZombieEnemiesAnimations;
typedef struct EnemiesAnimations
{
    ArmEnemiesAnimations* arm_enemies_animations;
    SkeletonEnemiesAnimations*skeleton_enemies_animations;
    ZombieEnemiesAnimations*zombie_enemies_animations;
    KnightZombieEnemiesAnimations*knight_zombie_enemies_animations;
    Animation attack_enemies_animation;
}EnemiesAnimations;
typedef struct CoinsAnimation
{
    Animation coins;

}CoinsAnimation;
typedef struct ExpAnimation
{
    Animation small_exp;
    Animation medium_exp;

}ExpAnimation;
typedef struct HealAnimation
{
    Animation small_heals;
    Animation medium_heals;

}HealAnimation;
typedef struct MiscellaneousAnimation
{
    HealAnimation* heals_animation;
    ExpAnimation*exps_animation;
    CoinsAnimation*coins_animation;
}MiscellaneousAnimation;
typedef struct HelmetAnimation
{
    Animation wooden_HELMET;
    Animation leather_HELMET;
    Animation iron_HELMET;
    Animation mithril_HELMET;
    Animation wooden_HELMET_no_line;
    Animation leather_HELMET_no_line;
    Animation iron_HELMET_no_line;
    Animation mithril_HELMET_no_line;

}HelmetAnimation;
typedef struct SwordAnimation
{
    Animation wooden_weapon;
    Animation stone_weapon;
    Animation iron_weapon;
    Animation mithril_weapon;
    Animation wooden_weapon_no_line;
    Animation stone_weapon_no_line;
    Animation iron_weapon_no_line;
    Animation mithril_weapon_no_line;

}SwordAnimation;
typedef struct ArmorAnimation
{
    Animation wooden_armor;
    Animation leather_armor;
    Animation iron_armor;
    Animation mithril_armor;
    Animation wooden_armor_no_line;
    Animation leather_armor_no_line;
    Animation iron_armor_no_line;
    Animation mithril_armor_no_line;

}ArmorAnimation;
typedef struct EquipmentAnimation
{
    ArmorAnimation* armors_animation;
    SwordAnimation* swords_animation;
    HelmetAnimation* helmets_animation;
}EquipmentAnimation;
typedef struct ItemsAnimation
{
    EquipmentAnimation* equipment_animation;
    MiscellaneousAnimation* misc_animation;
}ItemsAnimation;
typedef struct FloorAnimation
{
    Texture2D ground_floor;

}FloorAnimation;
typedef struct WallAnimation
{
    Animation ground_wall;

}WallAnimation;
typedef struct ActionTilesAnimations
{
    Animation tiles_backlight_animation;
    Animation tiles_backlight_glow_effect_animation_1;
    Animation tiles_backlight_glow_effect_animation_2;
    Animation tiles_backlight_glow_effect_animation_3;
    Animation tiles_backlight_glow_effect_animation_4;
    Animation tiles_backlight_line_animation_1;
    Animation tiles_backlight_line_animation_2;
    Animation tiles_backlight_line_animation_3;
    Animation tiles_backlight_line_animation_4;

}ActionTilesAnimations;
typedef struct TilesAnimation
{
    FloorAnimation* floor_animation;
    WallAnimation* wall_animation;
    ActionTilesAnimations* action_tiles_animations;
}TilesAnimation;
typedef struct WorldAnimation
{
    TilesAnimation* tiles_animation;
}WorldAnimation;
typedef struct Animations
{
    WorldAnimation* world_animation;
    ItemsAnimation* items_animation;
    EnemiesAnimations* enemies_animation;
    PlayersAnimations* player_animation;
    GUIAnimation* gui_animation;
}Animations;

#endif