#ifndef STRUCTURS_H
#define STRUCTURS_H
#include <stdlib.h> 
#include "raylib.h"
#include "Allocator.h"
//#include "PlayerLogic.h"
//#include "EnemyLogic.h"
//#include "ItemLogic.h"
//#include "MiscScripts.h"
//#include "AssetsLogic.h"

extern int enemy_indexes;
typedef struct Enemy Enemy;
typedef struct Animation Animation;
typedef struct Action Action;



typedef struct ActionPosInfo
{
    Vector2* position_pixels; //указатель на позицию обьекта
    Vector2 old_tile; //страый тайл
    Vector2 new_tile; //новый тайл

}ActionPos;
typedef struct ActionMainInfo
{
    int* movement_type; //тип движения 
    int during_type; //когда должно произойти
    int* action_type; //что должно произойти
}ActionMainInfo;
typedef struct ActionObjectInfo
{
    int object_type; //тип обьекта который это делает
    int object_index; //индекс обьекта на карте
    int affected_type;
    int affected_index;
}ActionObjectInfo;
typedef struct ActionMiscInfo
{
    float amount_full_moves;
    float current_fill; //типо таймера
    float max_fill; //макс заполнение таймера
    float speed; //скорость движения
    int current_state; //текущее состояние

}ActionMiscInfo;
typedef struct ActionQueueInfo
{
    Action* beginning_action;
    Action* ending_action;

}ActionQueueInfo;
typedef struct Action
{
    ActionMainInfo* main;
    ActionPos* pos;
    ActionObjectInfo* object;
    ActionMiscInfo* misc;
    int flow;
    ActionQueueInfo* queue;
    Allocator* alloc;
    
    
}Action;
typedef struct ActionsMap
{
    Action** actions_main_queue;
    int amount_actions_main_queue;
    Action**actions_effects_queue;
    int amount_actions_effects_queue;
    char** tiles_glow;
    int current_state;
}ActionsMap;

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
    Vector2 next_move;
    bool activated;
    int path_len;
}EnemyMisc;
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
    ActionsMap* actins_map;
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
    Texture2D armors_no_lines;
}ArmorTexturs;

typedef struct SwordTexturs
{
    Texture2D swords;
    Rectangle frames[4];
    Texture2D swords_no_lines;
}SwordTexturs;

typedef struct HelmetTexturs
{
    Texture2D helmets;
    Rectangle frames[4];
    Texture2D helmets_no_lines;
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
typedef struct PlayerHuman
{
    Texture2D human_textur;
}PlayerHuman;
typedef struct PlayerTexturs
{
    PlayerHuman* player_human;
    Texture2D heads_texturs;
}PlayerTexturs;
typedef struct Texturs
{
    WorldTexturs* world_texturs;
    ItemsTexturs* items_texturs;
    EnemiesTexturs* enemies_texturs;
    PlayerTexturs* player_texturs;
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
    float framesSpeed;
    float frameWidth;
    float frameHeight;
    bool isPlaying;
    int index;
}Animation ;



typedef struct PlayerCurrentEquipmentAnimations
{
    Animation** current_armor_anim;
    Animation** current_sword_anim;
    Animation** current_helmet_anim;
    
}PlayerCurrentEquipmentAnimations;
typedef struct PlayerEquipmentAnimations
{
    Animation armor_animation;
    Animation sword_animation;
    Animation helmet_animation;
    
}PlayerEquipmentAnimations;
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
typedef struct PlayerAnimations
{
    PlayerEquipmentAnimations* player_equipment_animation;
    PlayerActionAnimations*player_action_animation;
    PlayerHeadAnimations* player_head_animation;
}PlayerAnimations;
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
typedef struct SwordOffsetPos
{
    Vector2 current_pos;
    Vector2 offset;
    Vector2 alignment;
    float current_rotate;
}SwordOffsetPos;
typedef struct HeadOffsetPos
{
    Vector2 current_pos;
    Vector2 offset;
    Vector2 alignment;

}HeadOffsetPos;
typedef struct PlayerEquipmentOffsetPos
{
    ArmorOffsetPos* armor_pos;
    HelmetOffsetPos* helmet_pos;
    SwordOffsetPos* sword_pos;
    

}PlayerEquipmentOffsetPos;

typedef struct PlayerCurrentAnimations
{
    Animation** current_anim;
    Animation** current_head_anim;
    PlayerCurrentEquipmentAnimations* current_equipment_anim;
}PlayerCurrentAnimations;
typedef struct PlayerPos
{
    PlayerTilesPos* position_tiles;
    PlayerPixelsPos* position_pixels;
    HeadOffsetPos* head_pos;
    PlayerEquipmentOffsetPos* equipment_pos;

}PlayerPos;
typedef struct Player
{
    PlayerStats* player_stats;
    PlayerPos* player_pos;
    PlayerCurrentAnimations* current_animations;
    PlayerAnimations* player_anim;
}Player;
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
typedef struct EnemyActions
{
    Action* enemy_move;
    Action* enemy_attack;
    Action* enemy_die;
}EnemyActions;
typedef struct Enemy
{
    EnemyMain* enemy_main;
    EnemyCharacteristics* enemy_characteristics;
    EnemyPos* enemy_position;
    EnemyMisc* enemy_misc;
    EnemyAnimations* enemy_animations;
    EnemyActions* enemy_actions;
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
    Animation wooden_armor_no_line;
    Animation leather_armor_no_line;
    Animation iron_armor_no_line;
    Animation mithril_armor_no_line;

}ArmorAnimation;

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
}EnemiesAnimations;
typedef struct HumanAnimations
{
    Animation player_breathe_animation;
    Animation player_walk_animation;
    Animation player_attack_animation;
    Animation player_die_animation;
    Animation player_mine_animation;
    
}HumanAnimations;
typedef struct ArmorsEquipmentsAnimations
{
    Animation wooden_armor;
    Animation leather_armor;
    Animation iron_armor;
    Animation mithril_armor;
    
}ArmorsEquipmentsAnimations;
typedef struct SwordsEquipmentsAnimations
{
    Animation wooden_weapon;
    Animation stone_weapon;
    Animation iron_weapon;
    Animation mithril_weapon;
}SwordsEquipmentsAnimations;
typedef struct HelmetsEquipmentsAnimations
{
    Animation wooden_helmet;
    Animation leather_helmet;
    Animation iron_helmet;
    Animation mithril_helmet;
    
}HelmetsEquipmentsAnimations;

typedef struct PlayerEquipmentsAnimations
{
    ArmorsEquipmentsAnimations* armors;
    SwordsEquipmentsAnimations* swords;
    HelmetsEquipmentsAnimations* helmets;
}PlayerEquipmentsAnimations;
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
typedef struct PlayersAnimations
{
    HumanAnimations* human_animations;
    HumanHeadAnimations* human_head_animations;
    //PlayerEquipmentsAnimations* player_equipments_animations;
}PlayersAnimations;
typedef struct Animations
{
    WorldAnimation* world_animation;
    ItemsAnimation* items_animation;
    EnemiesAnimations* enemies_animation;
    PlayersAnimations* player_animation;
    GUIAnimation* gui_animation;
}Animations;



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
typedef struct AnimationPlayerMap
{
    Animation*** animation_map_queue;
    int amount_animation_map_queue;

}AnimationPlayerMap;
typedef struct AnimationMaps
{
    AnimationItemsMap* animation_items_map;
    AnimationEnemyMap* animation_enemies_map;
    AnimationPlayerMap* animation_player_map;

}AnimationMaps;
typedef struct GAME_DATA
{
    Player* player;
    Maps* maps;
    Allocators* allocators;
    Misc* misc;

}GAME_DATA;


typedef struct GAME_ANIM
{
    Animations* animations;
    Texturs* texturs;
    Allocator* anim_alloc;
    AnimationMaps* maps;

}GAME_ANIM;


Player *create_player(Allocator *alloc, int start_posX, int start_posY);

ActionsMap *create_action_map(Allocator *alloc, int tilesX, int tilesY);


Action *create_action(Allocator *alloc, int flow, int object_type, int object_index, int* movement_type, int* action_type, int during_type, int affected_type, int affected_index, Vector2 *position_pixels, Vector2 old_tile, Vector2 new_tile, float max_fill, float amount_full_anim, float speed);







GAME_DATA *create_game_data();

AnimationEnemyMap *create_anim_enemies_map(GAME_ANIM *game_anim);

AnimationPlayerMap *create_anim_player_map(GAME_ANIM *game_anim);

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
