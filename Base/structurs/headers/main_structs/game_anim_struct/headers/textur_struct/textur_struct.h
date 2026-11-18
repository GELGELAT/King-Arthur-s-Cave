#ifndef TEXTUR_STRUCT_H
#define TEXTUR_STRUCT_H
#include "raylib.h"

typedef struct PlayerHuman
{
    Texture2D human_textur;
}PlayerHuman;

typedef struct PlayerTexturs
{
    PlayerHuman* player_human;
    Texture2D heads_texturs;
}PlayerTexturs;
typedef struct WeaponEffects
{
    Texture2D weapon_attacks;
}WeaponEffects;
typedef struct EffectsTexturs
{
    WeaponEffects* weapon_effects;
}EffectsTexturs;

typedef struct GUITexturs
{
    
}GUITexturs;
typedef struct ArmEnemiesTexturs
{
    Texture2D arm_0_texturs;
    Texture2D arm_1_texturs;
}ArmEnemiesTexturs;
typedef struct SkeletonEnemiesTexturs
{
    Texture2D skeleton_texturs;
}SkeletonEnemiesTexturs;
typedef struct ZombieEnemiesTexturs
{
    Texture2D zombie_texturs;
}ZombieEnemiesTexturs;
typedef struct KnightZombieEnemiesTexturs
{
    Texture2D knight_zombie_texturs;
}KnightZombieEnemiesTexturs;
typedef struct EnemiesTexturs
{
    ArmEnemiesTexturs* arm_enemies_textur;
    SkeletonEnemiesTexturs*skeleton_enemies_textur;
    ZombieEnemiesTexturs*zombie_enemies_textur;
    KnightZombieEnemiesTexturs*knight_zombie_enemies_textur;
}EnemiesTexturs;
typedef struct HealTexturs
{
    Texture2D heals;
    Rectangle small_frames;
    Rectangle medium_frames;
}HealTexturs;
typedef struct ExpTexturs
{
    Texture2D exps;
    Rectangle small_frames[4];
    Rectangle medium_frames[4];
}ExpTexturs;
typedef struct CoinsTexturs
{
    Texture2D coins;
    Rectangle small_frames[4];
    Rectangle medium_frames[4];
}CoinsTexturs;
typedef struct MiscellaneousTexturs
{
    HealTexturs* heals_texturs;
    ExpTexturs*exps_texturs;
    CoinsTexturs*coins_texturs;
}MiscellaneousTexturs;
typedef struct HelmetTexturs
{
    Texture2D helmets;
    Rectangle frames[4];
    Texture2D helmets_no_lines;
}HelmetTexturs;
typedef struct ArmorTexturs
{
    Texture2D armors;
    Rectangle frames[4];
    Texture2D armors_no_lines;
}ArmorTexturs;

typedef struct SwordTexturs
{
    Texture2D swords;
    Rectangle frames[4];
    Texture2D swords_no_lines;
}SwordTexturs;

typedef struct EquipmentTexturs
{
    ArmorTexturs* armors_texturs;
    SwordTexturs* swords_texturs;
    HelmetTexturs* helmets_texturs;
}EquipmentTexturs;
typedef struct ItemsTexturs
{
    EquipmentTexturs* equipment_texturs;
    MiscellaneousTexturs* misc_texturs;
}ItemsTexturs;
typedef struct ActionTilesTexturs
{
    Texture2D tiles_backlight;
    Texture2D tiles_backlight_glow_effect;
    Texture2D tiles_backlight_line;
}ActionTilesTexturs;
typedef struct WallTexturs
{
    Texture2D ground_wall;
    Rectangle frames[4];
}WallTexturs;
typedef struct FloorTexturs
{
    Texture2D ground_floor;
    Rectangle frames[4];
}FloorTexturs;
typedef struct TilesTexturs
{
    FloorTexturs* floor_texturs;
    WallTexturs* wall_texturs;
    ActionTilesTexturs* action_tiles_texturs;
}TilesTexturs;
typedef struct WorldTexturs
{
    TilesTexturs* tiles_texturs;
    
}WorldTexturs;
typedef struct Texturs
{
    WorldTexturs* world_texturs;
    ItemsTexturs* items_texturs;
    EnemiesTexturs* enemies_texturs;
    PlayerTexturs* player_texturs;
    EffectsTexturs* effects_texturs;
    GUITexturs* gui_texturs;
}Texturs;
#endif