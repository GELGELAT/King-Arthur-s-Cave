#ifndef STRUCTURS_H
#define STRUCTURS_H
#include <stdlib.h> 
#include "raylib.h"
#include "allocator.h"
//#include "player_logic.h"
//#include "enemy_logic.h"
//#include "items_logic.h"
//#include "misc.h"
//#include "texturs.h"

extern int enemy_indexes;
typedef struct Enemy Enemy;
typedef struct Action
{
    Vector2* position_pixels;
    Vector2 old_tile;
    Vector2 new_tile;
    float current_fill;
    float speed;
    int current_state;
    int action;
    int index_enemies;
}Action;
typedef struct ActionMap
{
    Action* actions_queue;
    int amount_actions;

}ActionMap;

typedef struct ItemMain
{
    char* name;
    int index;
    int value;
    int textur_index;
    int pos_index;
}ItemMain;

typedef struct ItemTilesPos
{
    Vector2 pos_tiles;

}ItemTilesPos;
typedef struct ItemPixelsPos
{
    Vector2 pos_pixels;

}ItemPixelsPos;

typedef struct ItemPos
{
    ItemTilesPos* position_tiles;
    ItemPixelsPos* position_pixels;


}ItemPos;
typedef struct EnemyMisc
{

    bool activated;
    int path_len;
}EnemyMisc;
typedef struct EnemyCharacteristics
{
    int heal_points;
    int defense;
    int max_physical_damage;
    int min_physical_damage;
}EnemyCharacteristics;
typedef struct EnemyMain
{
    char* name;
    int index;
}EnemyMain;
typedef struct EnemyTilesPos
{
    Vector2 pos_tiles;

}EnemyTilesPos;
typedef struct EnemyPixelsPos
{
    Vector2 pos_pixels;

}EnemyPixelsPos;

typedef struct EnemyPos
{
    EnemyTilesPos* position_tiles;
    EnemyPixelsPos* position_pixels;


}EnemyPos;
typedef struct PlayerTilesPos
{
    Vector2 pos_tiles;

}PlayerTilesPos;
typedef struct PlayerPixelsPos
{
    Vector2 pos_pixels;

}PlayerPixelsPos;
typedef struct PlayerPos
{
    PlayerTilesPos* position_tiles;
    PlayerPixelsPos* position_pixels;


}PlayerPos;

typedef struct PlayerExp
{
    int experience_points;

    int level;
}PlayerExp;
typedef struct PlayerCoins
{
    int coins;

}PlayerCoins;
typedef struct PlayerEquipmentTier
{
    int armor_tier;
    int sword_tier;
    int HELMET_tier;

}PlayerEquipmentTier;
typedef struct PlayerCharacteristics
{
    int heal_points;
    int defense;
    int max_physical_damage;
    int min_physical_damage;

}PlayerCharacteristics;


typedef struct PlayerStats
{
    PlayerExp* player_exp;
    PlayerCoins* player_coins;
    PlayerEquipmentTier* player_equipment_tier;
    PlayerCharacteristics* player_characteristics;

}PlayerStats;
typedef struct Path
{
    Vector2** parents_position_tiles;
    char** visited_tiles;


}Path;

typedef struct Item
{
    ItemMain* item_main;
    ItemPos* item_position;

}Item;

typedef struct ItemsMap
{
    int** index_map;
    Item** items_map;
    int items_map_amount;
}ItemsMap;


typedef struct EnemyMap
{
    Enemy** move_queue;
    int move_queue_amount;
    Enemy** enemy_map;
    int enemy_map_amount;
    int** index_map;
}EnemyMap;




typedef struct Cell
{
    char** objects;
    Vector2 positin;
    int amount_objects;
}Cell;

typedef struct CellsMap
{
    Cell*** cells;
    int tilesX;
    int tilesY;
    int tileSize;
}CellsMap;

typedef struct FogMap
{
    char** grid;
    int tilesX;
    int tilesY;
}FogMap;
typedef struct CollisionMap
{
    char** grid;
    int tilesX;
    int tilesY;
}CollisionMap;


typedef struct SpeedAnim
{
    float player_movement;
}SpeedAnim;


typedef struct Player
{
    PlayerPos* player_pos;
    PlayerStats* player_stats;
}Player;
typedef struct MonitorSize
{
    int monitor_width;
    int monitor_height;
}MonitorSize;
typedef struct Allocators
{
    Allocator* alloc_data;
    Allocator* alloc_misc;
    
}Allocators;

typedef struct Misc
{
    Camera2D camera;
    MonitorSize monitor_size;
    Path* path;
    SpeedAnim* speed_anim;
}Misc;
typedef struct Maps
{
    CellsMap* cells_map;
    CollisionMap* collision_map;
    FogMap* fog_map;
    ItemsMap* items_map;
    EnemyMap* enemy_map;
    ActionMap* pos_map;
}Maps;


typedef struct FloorTexturs
{
    Texture2D ground_floor;
    Rectangle frames[4];
}FloorTexturs;
typedef struct WallTexturs
{
    Texture2D ground_wall;
    Rectangle frames[4];
}WallTexturs;

typedef struct TilesTexturs
{
    FloorTexturs* floor_texturs;
    WallTexturs* wall_texturs;
}TilesTexturs;
typedef struct WorldTexturs
{
    TilesTexturs* tiles_texturs;
}WorldTexturs;
typedef struct GUITexturs
{
    
}GUITexturs;

typedef struct ArmorTexturs
{
    Texture2D armors;
    Rectangle frames[4];
}ArmorTexturs;

typedef struct SwordTexturs
{
    Texture2D swords;
    Rectangle frames[4];
}SwordTexturs;

typedef struct HelmetTexturs
{
    Texture2D helmets;
    Rectangle frames[4];
}HelmetTexturs;

typedef struct EquipmentTexturs
{
    ArmorTexturs* armors_texturs;
    SwordTexturs* swords_texturs;
    HelmetTexturs* helmets_texturs;
}EquipmentTexturs;
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
typedef struct ItemsTexturs
{
    EquipmentTexturs* equipment_texturs;
    MiscellaneousTexturs* misc_texturs;
}ItemsTexturs;

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
typedef struct Texturs
{
    WorldTexturs* world_texturs;
    ItemsTexturs* items_texturs;
    EnemiesTexturs* enemies_texturs;
    GUITexturs* gui_texturs;
}Texturs;

typedef struct Animation  
{
    Texture2D texture;
    Rectangle cur_frameRec;
    Rectangle start_frameRec;
    int direction;
    int currentFrame;
    int frameCount;
    int framesCounter;
    int framesSpeed;
    float frameWidth;
    float frameHeight;
    bool isPlaying;
    int index;
}Animation ;
typedef struct EnemyAnimations
{
    Animation breathe;
    Animation attack;
    Animation walk;
    Animation die;
    int size_x;
    int size_y;
    int alignment_x;
    int alignment_y
}EnemyAnimations;
typedef struct Enemy
{
    EnemyMain* enemy_main;
    EnemyCharacteristics* enemy_characteristics;
    EnemyPos* enemy_position;
    EnemyMisc* enemy_misc;
    EnemyAnimations* enemy_animations;
    Animation** current_animation;
}Enemy;
typedef struct FloorAnimation
{
    Texture2D ground_floor;

}FloorAnimation;
typedef struct WallAnimation
{
    Animation ground_wall;

}WallAnimation;

typedef struct TilesAnimation
{
    FloorAnimation* floor_animation;
    WallAnimation* wall_animation;
}TilesAnimation;
typedef struct WorldAnimation
{
    TilesAnimation* tiles_animation;
}WorldAnimation;
typedef struct GUIAnimation
{
    
}GUIAnimation;

typedef struct ArmorAnimation
{
    Animation wooden_armor;
    Animation leather_armor;
    Animation iron_armor;
    Animation mithril_armor;

}ArmorAnimation;

typedef struct SwordAnimation
{
    Animation wooden_weapon;
    Animation stone_weapon;
    Animation iron_weapon;
    Animation mithril_weapon;

}SwordAnimation;

typedef struct HelmetAnimation
{
    Animation wooden_HELMET;
    Animation leather_HELMET;
    Animation iron_HELMET;
    Animation mithril_HELMET;

}HelmetAnimation;

typedef struct EquipmentAnimation
{
    ArmorAnimation* armors_animation;
    SwordAnimation* swords_animation;
    HelmetAnimation* helmets_animation;
}EquipmentAnimation;
typedef struct HealAnimation
{
    Animation small_heals;
    Animation medium_heals;

}HealAnimation;
typedef struct ExpAnimation
{
    Animation small_exp;
    Animation medium_exp;

}ExpAnimation;
typedef struct CoinsAnimation
{
    Animation coins;

}CoinsAnimation;
typedef struct MiscellaneousAnimation
{
    HealAnimation* heals_animation;
    ExpAnimation*exps_animation;
    CoinsAnimation*coins_animation;
}MiscellaneousAnimation;
typedef struct ItemsAnimation
{
    EquipmentAnimation* equipment_animation;
    MiscellaneousAnimation* misc_animation;
}ItemsAnimation;
typedef struct ArmEnemiesAnimations
{
    Animation arm_0_breathe_animation;
    Animation arm_0_walk_animation;
    Animation arm_0_attack_animation;
    Animation arm_0_die_animation;
    Animation arm_1_breathe_animation;
    Animation arm_1_walk_animation;
    Animation arm_1_attack_animation;
    Animation arm_1_die_animation;
}ArmEnemiesAnimations;
typedef struct SkeletonEnemiesAnimations
{
    Animation skeleton_breathe_animation;
    Animation skeleton_walk_animation;
    Animation skeleton_attack_animation;
    Animation skeleton_die_animation;
}SkeletonEnemiesAnimations;
typedef struct ZombieEnemiesAnimations
{
    Animation zombie_breathe_animation;
    Animation zombie_walk_animation;
    Animation zombie_attack_animation;
    Animation zombie_die_animation;
}ZombieEnemiesAnimations;
typedef struct KnightZombieEnemiesAnimations
{
    Texture2D knight_zombie_animation;
    Animation knight_zombie_breathe_animation;
    Animation knight_zombie_walk_animation;
    Animation knight_zombie_attack_animation;
    Animation knight_zombie_die_animation;
}KnightZombieEnemiesAnimations;
typedef struct EnemiesAnimations
{
    ArmEnemiesAnimations* arm_enemies_animations;
    SkeletonEnemiesAnimations*skeleton_enemies_animations;
    ZombieEnemiesAnimations*zombie_enemies_animations;
    KnightZombieEnemiesAnimations*knight_zombie_enemies_animations;
}EnemiesAnimations;
typedef struct Animations
{
    WorldAnimation* world_animation;
    ItemsAnimation* items_animation;
    EnemiesAnimations* enemies_animation;
    GUIAnimation* gui_animation;
}Animations;

typedef struct GAME_DATA
{
    Player* player;
    Maps* maps;
    Allocators* allocators;
    Misc* misc;

}GAME_DATA;

typedef struct AnimationItemsMap
{
    Animation* animation_map;
    Animation** animation_map_queue;
    int amount_animation_map_queue;

}AnimationItemsMap;
typedef struct AnimationEnemyMap
{
    Animation*** animation_map_queue;
    int amount_animation_map_queue;

}AnimationEnemyMap;
typedef struct AnimationMaps
{
    AnimationItemsMap* animation_items_map;
    AnimationEnemyMap* animation_enemies_map;

}AnimationMaps;



typedef struct GAME_ANIM
{
    Animations* animations;
    Texturs* texturs;
    Allocator* anim_alloc;
    AnimationMaps* maps;

}GAME_ANIM;


Player *create_player(Allocator *alloc, int start_posX, int start_posY);

ActionMap *create_action_map(Allocator *alloc);

Action create_action(Allocator *alloc, Vector2 *position_pixels, Vector2 old_tile, Vector2 new_tile, float speed, int cur_action, int index_enemies);



GAME_DATA *create_game_data();

AnimationEnemyMap *create_anim_enemies_map(GAME_ANIM *game_anim);

AnimationItemsMap *create_anim_items_map(GAME_ANIM *game_anim);

GAME_ANIM *create_game_anim();

ItemsMap *create_items_map(Allocator *alloc, int tilesX, int tilesY);

Cell *create_cell(Allocator *alloc);

FogMap *create_fog_map(Allocator *alloc, int tilesX, int tilesY);

CellsMap *create_cells_map(Allocator *alloc, int tilesX, int tilesY, int tileSize);

CollisionMap *create_collision_map(Allocator *alloc, int tilesX, int tilesY);


EnemyMap *create_enemy_map(Allocator *alloc, int enemy_indexes, int tilesX, int tilesY);

void raw_initialization_cells(Allocator *alloc, CellsMap *cells_map);

Path *create_path_structur(Allocator *alloc, int tilesX, int tilesY);

#endif
