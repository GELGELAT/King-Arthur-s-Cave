#include "TextursInit.h"


Texturs* create_texturs_struct(Allocator* alloc)
{
    Texturs* texturs = alloc_alloc(alloc,sizeof(Texturs));
    GUITexturs* gui_texturs = alloc_alloc(alloc,sizeof(GUITexturs));
    WorldTexturs* world_texturs = alloc_alloc(alloc,sizeof(WorldTexturs));
    TilesTexturs* tiles_texturs = alloc_alloc(alloc,sizeof(TilesTexturs));
    FloorTexturs* floor_texturs = alloc_alloc(alloc,sizeof(FloorTexturs));
    WallTexturs* wall_texturs = alloc_alloc(alloc,sizeof(WallTexturs));
    ItemsTexturs*items_texturs = alloc_alloc(alloc,sizeof(ItemsTexturs));
    EquipmentTexturs* equipment_texturs = alloc_alloc(alloc,sizeof(EquipmentTexturs));

    MiscellaneousTexturs* misc_texturs = alloc_alloc(alloc,sizeof(MiscellaneousTexturs));
    ArmorTexturs* armors_texturs = alloc_alloc(alloc,sizeof(ArmorTexturs));
    HelmetTexturs* helmets_texturs = alloc_alloc(alloc,sizeof(HelmetTexturs));
    SwordTexturs* swords_texturs = alloc_alloc(alloc,sizeof(SwordTexturs));
    CoinsTexturs* coins_texturs = alloc_alloc(alloc,sizeof(CoinsTexturs));
    ExpTexturs* exps_texturs = alloc_alloc(alloc,sizeof(ExpTexturs));
    HealTexturs* heals_texturs = alloc_alloc(alloc,sizeof(HealTexturs));

    EnemiesTexturs* enemies_texturs = alloc_alloc(alloc,sizeof(EnemiesTexturs));

    ArmEnemiesTexturs* arm_enemies_textur = alloc_alloc(alloc,sizeof(ArmEnemiesTexturs));
    SkeletonEnemiesTexturs* skeleton_enemies_textur = alloc_alloc(alloc,sizeof(SkeletonEnemiesTexturs));
    KnightZombieEnemiesTexturs* knight_zombie_enemies_textur = alloc_alloc(alloc,sizeof(KnightZombieEnemiesTexturs));
    ZombieEnemiesTexturs* zombie_enemies_textur = alloc_alloc(alloc,sizeof(ZombieEnemiesTexturs));
    texturs->enemies_texturs =enemies_texturs;
    texturs->enemies_texturs->arm_enemies_textur = arm_enemies_textur;
    texturs->enemies_texturs->skeleton_enemies_textur =skeleton_enemies_textur;
    texturs->enemies_texturs->knight_zombie_enemies_textur =knight_zombie_enemies_textur;
    texturs->enemies_texturs->zombie_enemies_textur = zombie_enemies_textur;

    texturs->items_texturs=items_texturs;
    texturs->items_texturs->equipment_texturs=equipment_texturs;
    texturs->items_texturs->misc_texturs=misc_texturs;
    texturs->items_texturs->equipment_texturs->armors_texturs=armors_texturs;
    texturs->items_texturs->equipment_texturs->helmets_texturs=helmets_texturs;
    texturs->items_texturs->equipment_texturs->swords_texturs=swords_texturs;
    texturs->items_texturs->misc_texturs->coins_texturs=coins_texturs;
    texturs->items_texturs->misc_texturs->exps_texturs=exps_texturs;
    texturs->items_texturs->misc_texturs->heals_texturs=heals_texturs;

    texturs->gui_texturs = gui_texturs;
    texturs->world_texturs = world_texturs;
    texturs->world_texturs->tiles_texturs= tiles_texturs;
    texturs->world_texturs->tiles_texturs->floor_texturs = floor_texturs;
    texturs->world_texturs->tiles_texturs->wall_texturs = wall_texturs;
    PlayerTexturs * player_texturs = alloc_alloc(alloc,sizeof(PlayerTexturs ));
    PlayerHuman  * player_human = alloc_alloc(alloc,sizeof(PlayerHuman  ));

    texturs->player_texturs =player_texturs;
    texturs->player_texturs->player_human = player_human;
    return texturs;
}
void texturs_init(GAME_ANIM* game_anim)
{
    game_anim->texturs = create_texturs_struct(game_anim->anim_alloc);
    tiles_textur_init(game_anim);
    mics_items_textur_init(game_anim);
    equipment_textur_init(game_anim);
    enemies_textur_init(game_anim);
    player_textur_init(game_anim);
}

void mics_items_textur_init(GAME_ANIM* game_anim)
{
    Texture2D exp_texturs = LoadTexture("Texturs/Items/Misc/exp.png");
    Texture2D heal_texturs = LoadTexture("Texturs/Items/Misc/heal.png");
    Texture2D coins_texturs = LoadTexture("Texturs/Items/Misc/coins.png");
    game_anim->texturs->items_texturs->misc_texturs->coins_texturs->coins = coins_texturs;
    game_anim->texturs->items_texturs->misc_texturs->exps_texturs->exps =exp_texturs;
    game_anim->texturs->items_texturs->misc_texturs->heals_texturs->heals = heal_texturs;
    Rectangle frames_tiles_small[4] = {0};
    Rectangle frames_tiles_medium[4] = {0};
    Rectangle sprite_tiles_small[1] = {0};
    Rectangle sprite_tiles_medium[1] = {0};
    for (int i = 0; i<4;i++)
    {
        game_anim->texturs->items_texturs->misc_texturs->exps_texturs->small_frames[i] = (Rectangle){0,i*32,32,32};
        game_anim->texturs->items_texturs->misc_texturs->exps_texturs->medium_frames[i] = (Rectangle){32,i*32,32,32};

        game_anim->texturs->items_texturs->misc_texturs->coins_texturs->small_frames[i] = (Rectangle){0,i*32,32,32};
        game_anim->texturs->items_texturs->misc_texturs->coins_texturs->medium_frames[i] = (Rectangle){32,i*32,32,32};

    }
    game_anim->texturs->items_texturs->misc_texturs->heals_texturs->small_frames=(Rectangle){0,32,32,32};
    game_anim->texturs->items_texturs->misc_texturs->heals_texturs->medium_frames=(Rectangle){0,64,32,32};
}
void equipment_textur_init(GAME_ANIM* game_anim)
{
    Texture2D armor_texturs = LoadTexture("Texturs/Equipment/Armor/armor.png");

    game_anim->texturs->items_texturs->equipment_texturs->armors_texturs->armors=armor_texturs;
    Texture2D weapon_texturs = LoadTexture("Texturs/Equipment/Swords/swords.png");
    game_anim->texturs->items_texturs->equipment_texturs->swords_texturs->swords=weapon_texturs;
    Texture2D helmets_texturs = LoadTexture("Texturs/Equipment/Helmets/helmets.png");
    game_anim->texturs->items_texturs->equipment_texturs->helmets_texturs->helmets=helmets_texturs;

}
void enemies_textur_init(GAME_ANIM* game_anim)
{
    Texture2D skeleton_texturs = LoadTexture("Texturs/Enemies/Skeleton/Skeleton.png");

    game_anim->texturs->enemies_texturs->skeleton_enemies_textur->skeleton_texturs = skeleton_texturs;

    Texture2D arm_1_texturs = LoadTexture("Texturs/Enemies/Arm/Arm.png");
    Texture2D arm_0_texturs = LoadTexture("Texturs/Enemies/Arm/ZombieChicken.png");
    game_anim->texturs->enemies_texturs->arm_enemies_textur->arm_0_texturs =arm_0_texturs;
    game_anim->texturs->enemies_texturs->arm_enemies_textur->arm_1_texturs = arm_1_texturs;

    Texture2D zombie_texturs = LoadTexture("Texturs/Enemies/Zombie/Zombie_Variation0.png");
    game_anim->texturs->enemies_texturs->zombie_enemies_textur->zombie_texturs =zombie_texturs;

    Texture2D knight_zombie_enemies_textur = LoadTexture("Texturs/Enemies/ZombieKnight/ZombieKnight.png");
    game_anim->texturs->enemies_texturs->knight_zombie_enemies_textur->knight_zombie_texturs =knight_zombie_enemies_textur;
}
void player_textur_init(GAME_ANIM* game_anim)
{
    Texture2D player_human = LoadTexture("Texturs/Player/player_human.png");

    game_anim->texturs->player_texturs->player_human->human_textur = player_human;


}

void tiles_textur_init(GAME_ANIM* game_anim)
{
    Texture2D ground_floor_texturs = LoadTexture("Texturs/Tiles/floors_ground.png");
    Texture2D ground_wall_texturs = LoadTexture("Texturs/Tiles/walls_ground.png");
    game_anim->texturs->world_texturs->tiles_texturs->wall_texturs->ground_wall = ground_wall_texturs;
    game_anim->texturs->world_texturs->tiles_texturs->floor_texturs->ground_floor = ground_floor_texturs;
    Rectangle frames_tiles[4] = {0};
    for (int i = 0; i<4;i++)
    {
        game_anim->texturs->world_texturs->tiles_texturs->floor_texturs->frames[i] = (Rectangle){i*64,0,64,64};
        game_anim->texturs->world_texturs->tiles_texturs->wall_texturs->frames[i] = (Rectangle){i*64,0,64,64};
    }
}
