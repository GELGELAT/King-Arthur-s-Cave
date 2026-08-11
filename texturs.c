#include "texturs.h"




char* floor_texturs[] = {"floor_0","floor_1","floor_2","floor_3"};
char* wall_texturs[] = {"wall_0","wall_1","wall_2","wall_3"};
char* player_texturs = "player";
char* fog_texturs = "fog";

char* enemy_texturs[] = {"hand","sceleton","zombi","heavy_zombi"};

char* armor_chest_texturs[] = {"wooden_armor","leather_armor","iron_armor","mithril_armor"};
char* weapon_texturs[] = {"wooden_weapon","stone_weapon","iron_weapon","mithril_weapon"};
char* HELMET_texturs[] = {"wooden_HELMET","leather_HELMET","iron_HELMET","mithril_HELMET"};

char* coins_texturs[] = {"coins","bag_of_coins","chest_of_coins"};
char* heals_texturs[] = {"bubble_of_heal","bottle_of_heal","essence_of_heal"};
char* experience_texturs[] = {"experience","bunch_of_experience","essence_of_experience"};



Color color_floor_texturs[] = {{130,130,130,255},{125,125,125,255},{135,135,135,255},{120,120,120,255}};
Color color_wall_texturs[] = {{15,15,15,255},{20,20,20,255},{25,25,25,255},{30,30,30,255}};
Color color_enemy_texturs[] = {{50, 194, 21,255},{188, 194, 21,255},{194, 119, 21,255},{194, 21, 21,255}};

Color color_armor_chest_texturs[] = {{50, 194, 21,255},{188, 194, 21,255},{194, 119, 21,255},{194, 21, 21,255}};
Color color_weapon_texturs[] = {{50, 194, 21,255},{188, 194, 21,255},{194, 119, 21,255},{194, 21, 21,255}};
Color color_HELMET_texturs[] = {{50, 194, 21,255},{188, 194, 21,255},{194, 119, 21,255},{194, 21, 21,255}};



char* textur(int index,int textur_index)
{
    if (index == 1)
    {
        return floor_texturs[rand_num_within(0,3)];
    }
    else if (index == 2)
    {
        return wall_texturs[rand_num_within(0,3)];
    }
    else if (index == 3)
    {
        return player_texturs;
    }
    else if (index == 4)
    {
        return enemy_texturs[textur_index];
    }
    else if (index == 5)
    {
        return armor_chest_texturs[textur_index];
    }
    else if (index == 6)
    {
        return weapon_texturs[textur_index];
    }
    else if (index == 7)
    {
        return HELMET_texturs[textur_index];
    }
    else if (index == 8)
    {
        return coins_texturs[textur_index];
    }
    else if (index == 9)
    {
        return heals_texturs[textur_index];
    }
    else if (index == 10)
    {
        return experience_texturs[textur_index];
    }
}

void texturs_init(GAME_ANIM* game_anim)
{
    game_anim->texturs = create_texturs_struct(game_anim->anim_alloc);
    tiles_textur_init(game_anim);
    mics_items_textur_init(game_anim);
    equipment_textur_init(game_anim);
    enemies_textur_init(game_anim);

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
    
    return texturs;
}

Animations* create_animations_struct(Allocator* alloc)
{
    Animations* animation = alloc_alloc(alloc,sizeof(Texturs));
    GUIAnimation* gui_animation = alloc_alloc(alloc,sizeof(GUIAnimation));
    WorldAnimation* world_animation = alloc_alloc(alloc,sizeof(WorldAnimation));
    TilesAnimation* tiles_animation = alloc_alloc(alloc,sizeof(TilesAnimation));
    FloorAnimation* floor_animation = alloc_alloc(alloc,sizeof(FloorAnimation));
    WallAnimation* wall_animation = alloc_alloc(alloc,sizeof(WallAnimation));
    ItemsAnimation*items_animation = alloc_alloc(alloc,sizeof(ItemsAnimation));
    EquipmentAnimation* equipment_animation = alloc_alloc(alloc,sizeof(EquipmentAnimation));

    MiscellaneousAnimation* misc_animation = alloc_alloc(alloc,sizeof(MiscellaneousAnimation));
    ArmorAnimation* armors_animation = alloc_alloc(alloc,sizeof(ArmorAnimation));
    HelmetAnimation* helmets_animation = alloc_alloc(alloc,sizeof(HelmetAnimation));
    SwordAnimation* swords_animation = alloc_alloc(alloc,sizeof(SwordAnimation));
    CoinsAnimation* coins_animation = alloc_alloc(alloc,sizeof(CoinsAnimation));
    ExpAnimation* exps_animation = alloc_alloc(alloc,sizeof(ExpAnimation));
    HealAnimation* heals_animation = alloc_alloc(alloc,sizeof(HealAnimation));


    EnemiesAnimations* enemies_animation = alloc_alloc(alloc,sizeof(EnemiesAnimations));

    ArmEnemiesAnimations* arm_enemies_animations = alloc_alloc(alloc,sizeof(ArmEnemiesAnimations));
    SkeletonEnemiesAnimations* skeleton_enemies_animations = alloc_alloc(alloc,sizeof(SkeletonEnemiesAnimations));
    KnightZombieEnemiesAnimations* knight_zombie_enemies_animations = alloc_alloc(alloc,sizeof(KnightZombieEnemiesAnimations));
    ZombieEnemiesAnimations* zombie_enemies_animations = alloc_alloc(alloc,sizeof(ZombieEnemiesAnimations));
    animation->enemies_animation =enemies_animation;
    animation->enemies_animation->arm_enemies_animations = arm_enemies_animations;
    animation->enemies_animation->skeleton_enemies_animations =skeleton_enemies_animations;
    animation->enemies_animation->knight_zombie_enemies_animations =knight_zombie_enemies_animations;
    animation->enemies_animation->zombie_enemies_animations = zombie_enemies_animations;

    animation->items_animation=items_animation;
    animation->items_animation->equipment_animation=equipment_animation;
    animation->items_animation->misc_animation=misc_animation;
    animation->items_animation->equipment_animation->armors_animation=armors_animation;
    animation->items_animation->equipment_animation->helmets_animation=helmets_animation;
    animation->items_animation->equipment_animation->swords_animation=swords_animation;
    animation->items_animation->misc_animation->coins_animation=coins_animation;
    animation->items_animation->misc_animation->exps_animation=exps_animation;
    animation->items_animation->misc_animation->heals_animation=heals_animation;

    animation->gui_animation = gui_animation;
    animation->world_animation = world_animation;
    animation->world_animation->tiles_animation= tiles_animation;
    animation->world_animation->tiles_animation->floor_animation = floor_animation;
    animation->world_animation->tiles_animation->wall_animation = wall_animation;

    
    return animation;
}
Animation create_animation(Texture2D textur,int direction,int frame_count,int frame_width,int frame_height,Rectangle start_frame,int anim_speed,Allocator* alloc)
{
    Animation animation = {0};
    animation.direction = direction;
    animation.texture = textur;
    animation.currentFrame = 0;
    animation.frameCount =frame_count;
    animation.frameHeight =frame_height;
    animation.frameWidth=frame_width;
    animation.cur_frameRec =start_frame;
    animation.start_frameRec =start_frame;
    animation.framesSpeed =anim_speed;
    animation.isPlaying = true;
    animation.framesCounter=0;
    return animation;
}
/*
Animation* create_animation(Texture2D textur,int direction,int frame_count,int frame_width,int frame_height,Rectangle start_frame,int anim_speed,Allocator* alloc)
{
    Animation* animation = alloc_alloc(alloc,sizeof(Animation));
    animation->direction = direction;
    animation->texture = textur;
    animation->currentFrame = 0;
    animation->frameCount =frame_count;
    animation->frameHeight =frame_height;
    animation->frameWidth=frame_width;
    animation->cur_frameRec =start_frame;
    animation->framesSpeed =anim_speed;
    animation->isPlaying = false;
    animation->framesCounter=0;
}
*/
void update_animation(Animation* anim)
{
    
    if (!anim->isPlaying)
    {
        return;
    }
    int direction = anim->direction;
    if (anim->frameCount == 1)
    {
        return;
    }
    //pr_int(anim->currentFrame);
    //pr_int(anim->texture.id);
    anim->framesCounter+=1;
    if (anim->framesCounter >= (60 / anim->framesSpeed)) 
    {
        anim->framesCounter = 0;
        anim->currentFrame++;
        
        if (anim->currentFrame >= anim->frameCount) 
        {
            anim->currentFrame = 0;
        }
        if (direction == Width)
        {
            anim->cur_frameRec.x = anim->start_frameRec.x+ (anim->currentFrame * anim->frameWidth);
        }
        else
        {
            anim->cur_frameRec.y = anim->start_frameRec.y+ (anim->currentFrame * anim->frameHeight);
        }
    
    }
}
void update_items_animations(GAME_ANIM* game_anim)
{
    
    for (int i=0;i< game_anim->maps->animation_items_map->amount_animation_map_queue;i++)
    {
        //pr_int(game_anim->maps->animation_items_map->animation_map_queue[i]->framesCounter);
        //Animation anim = ;
        update_animation(game_anim->maps->animation_items_map->animation_map_queue[i]);
    }
}

void draw_animation(Animation* anim,Vector2 pos,int size_x,int size_y,int pos_index,float rotate) 
{
    int rand_pos[5][2] = {{0,0},{0,32},{32,0},{32,32},{0,0}};
    if (!anim->isPlaying)
    {
        return;
    }
    Rectangle dest = {pos.x+rand_pos[pos_index][0],pos.y+rand_pos[pos_index][1],size_x,size_y};
    DrawTexturePro(anim->texture,anim->cur_frameRec,dest,(Vector2){0,0}, rotate, WHITE);
}
Animation get_item_animation(GAME_ANIM* game_anim,int index)
{
    Animation* anim_map = game_anim->maps->animation_items_map->animation_map;
    return anim_map[index];
}
void append_item_anim_to_arr(GAME_ANIM* game_anim,Animation* anim)
{
    Animation** queue = game_anim->maps->animation_items_map->animation_map_queue;
    int amount_queue = game_anim->maps->animation_items_map->amount_animation_map_queue;
    Animation* map = game_anim->maps->animation_items_map->animation_map;

    
    queue[amount_queue] = anim;
    game_anim->maps->animation_items_map->amount_animation_map_queue +=1;
    
}
void append_item_anim_to_map(GAME_ANIM* game_anim,Animation anim,int index)
{
    Animation* map = game_anim->maps->animation_items_map->animation_map;
    map[index] = anim;
    

}
void create_animations(GAME_DATA* game_data,GAME_ANIM*game_anim)
{
    Allocator* alloc = game_anim->anim_alloc;
    //EXP
    Texture2D exp_textur = game_anim->texturs->items_texturs->misc_texturs->exps_texturs->exps;
    Animation small_exp_anim = create_animation(exp_textur,Height,4,32,32,(Rectangle){0,0,32,32},8,alloc);
    Animation medium_exp_anim = create_animation(exp_textur,Height,4,32,32,(Rectangle){32,0,32,32},8,alloc);
    game_anim->animations->items_animation->misc_animation->exps_animation->small_exp = small_exp_anim;
    game_anim->animations->items_animation->misc_animation->exps_animation->medium_exp = medium_exp_anim;
    //HEAL
    Texture2D heal_textur = game_anim->texturs->items_texturs->misc_texturs->heals_texturs->heals;
    Animation small_heal_anim = create_animation(heal_textur,Height,1,32,32,(Rectangle){0,64,32,32},8,alloc);
    Animation medium_heal_anim = create_animation(heal_textur,Height,2,32,32,(Rectangle){0,64,32,32},8,alloc);
    game_anim->animations->items_animation->misc_animation->heals_animation->small_heals =small_heal_anim;
    game_anim->animations->items_animation->misc_animation->heals_animation->medium_heals = medium_heal_anim;
    //ARMOR
    Texture2D armor_textur = game_anim->texturs->items_texturs->equipment_texturs->armors_texturs->armors;
    Animation wooden_armor = create_animation(armor_textur,Width,1,170,107,(Rectangle){0,0,17,17},8,alloc);
    Animation leather_armor = create_animation(armor_textur,Width,1,17,17,(Rectangle){17,0,17,17},8,alloc);
    Animation iron_armor = create_animation(armor_textur,Width,1,17,17,(Rectangle){34,0,17,17},8,alloc);
    Animation mithril_armor = create_animation(armor_textur,Width,1,17,17,(Rectangle){51,0,17,17},8,alloc);
    game_anim->animations->items_animation->equipment_animation->armors_animation->wooden_armor =wooden_armor;
     game_anim->animations->items_animation->equipment_animation->armors_animation->leather_armor =leather_armor;
      game_anim->animations->items_animation->equipment_animation->armors_animation->iron_armor =iron_armor;
       game_anim->animations->items_animation->equipment_animation->armors_animation->mithril_armor =mithril_armor;
    //WEAPON char* weapon_texturs[] = {"wooden_weapon","stone_weapon","iron_weapon","mithril_weapon"};

    Texture2D weapon_textur = game_anim->texturs->items_texturs->equipment_texturs->swords_texturs->swords;
    Animation wooden_weapon = create_animation(weapon_textur,Width,1,170,107,(Rectangle){0,0,17,17},8,alloc);
    Animation stone_weapon = create_animation(weapon_textur,Width,1,17,17,(Rectangle){17,0,17,17},8,alloc);
    Animation iron_weapon = create_animation(weapon_textur,Width,1,17,17,(Rectangle){34,0,17,17},8,alloc);
    Animation mithril_weapon = create_animation(weapon_textur,Width,1,17,17,(Rectangle){51,0,17,17},8,alloc);
    game_anim->animations->items_animation->equipment_animation->swords_animation->wooden_weapon =wooden_weapon;
    game_anim->animations->items_animation->equipment_animation->swords_animation->stone_weapon =stone_weapon;
    game_anim->animations->items_animation->equipment_animation->swords_animation->iron_weapon =iron_weapon;
    game_anim->animations->items_animation->equipment_animation->swords_animation->mithril_weapon =mithril_weapon;
    //HELMETS char* HELMET_texturs[] = {"wooden_HELMET","leather_HELMET","iron_HELMET","mithril_HELMET"};

    Texture2D helmet_textur = game_anim->texturs->items_texturs->equipment_texturs->helmets_texturs->helmets;
    Animation wooden_HELMET = create_animation(helmet_textur,Width,1,170,107,(Rectangle){0,0,17,17},8,alloc);
    Animation leather_HELMET = create_animation(helmet_textur,Width,1,17,17,(Rectangle){17,0,17,17},8,alloc);
    Animation iron_HELMET = create_animation(helmet_textur,Width,1,17,17,(Rectangle){34,0,17,17},8,alloc);
    Animation mithril_HELMET = create_animation(helmet_textur,Width,1,17,17,(Rectangle){51,0,17,17},8,alloc);
    game_anim->animations->items_animation->equipment_animation->helmets_animation->wooden_HELMET =wooden_HELMET;
    game_anim->animations->items_animation->equipment_animation->helmets_animation->leather_HELMET =leather_HELMET;
    game_anim->animations->items_animation->equipment_animation->helmets_animation->iron_HELMET =iron_HELMET;
    game_anim->animations->items_animation->equipment_animation->helmets_animation->mithril_HELMET =mithril_HELMET;

    //SKELETON ANIM
    Texture2D skeleton_textur = game_anim->texturs->enemies_texturs->skeleton_enemies_textur->skeleton_texturs;
    Animation skeleton_breathe_animation =create_animation(skeleton_textur,Width,4,32,32,(Rectangle){0,96,32,32},8,alloc);
    Animation skeleton_walk_animation =create_animation(skeleton_textur,Width,4,32,32,(Rectangle){0,0,32,32},16,alloc);
    Animation skeleton_attack_animation =create_animation(skeleton_textur,Width,4,32,32,(Rectangle){0,32,32,32},8,alloc);
    Animation skeleton_die_animation=create_animation(skeleton_textur,Width,4,32,32,(Rectangle){0,64,32,32},8,alloc);
    game_anim->animations->enemies_animation->skeleton_enemies_animations->skeleton_breathe_animation=skeleton_breathe_animation;
    game_anim->animations->enemies_animation->skeleton_enemies_animations->skeleton_walk_animation=skeleton_walk_animation;
    game_anim->animations->enemies_animation->skeleton_enemies_animations->skeleton_attack_animation=skeleton_attack_animation;
    game_anim->animations->enemies_animation->skeleton_enemies_animations->skeleton_die_animation=skeleton_die_animation;

    //ARM 0 ANIM
    Texture2D arm_0_textur = game_anim->texturs->enemies_texturs->arm_enemies_textur->arm_0_texturs;
    Animation arm_0_breathe_animation =create_animation(arm_0_textur,Width,4,16,16,(Rectangle){0,48,16,16},8,alloc);
    Animation arm_0_walk_animation =create_animation(arm_0_textur,Width,4,16,16,(Rectangle){0,0,16,16},16,alloc);
    Animation arm_0_attack_animation =create_animation(arm_0_textur,Width,4,16,16,(Rectangle){0,32,16,16},8,alloc);
    Animation arm_0_die_animation=create_animation(arm_0_textur,Width,3,16,16,(Rectangle){0,16,16,16},8,alloc);
    game_anim->animations->enemies_animation->arm_enemies_animations->arm_0_breathe_animation=arm_0_breathe_animation;
    game_anim->animations->enemies_animation->arm_enemies_animations->arm_0_walk_animation=arm_0_walk_animation;
    game_anim->animations->enemies_animation->arm_enemies_animations->arm_0_attack_animation=arm_0_attack_animation;
    game_anim->animations->enemies_animation->arm_enemies_animations->arm_0_die_animation=arm_0_die_animation;
    //ARM 1 ANIM
    Texture2D arm_1_textur = game_anim->texturs->enemies_texturs->arm_enemies_textur->arm_1_texturs;
    Animation arm_1_breathe_animation =create_animation(arm_1_textur,Width,3,16,16,(Rectangle){0,32,16,16},8,alloc);
    Animation arm_1_walk_animation =create_animation(arm_1_textur,Width,3,16,16,(Rectangle){0,0,16,16},16,alloc);
    Animation arm_1_attack_animation =create_animation(arm_1_textur,Width,3,16,16,(Rectangle){0,16,16,16},8,alloc);
    Animation arm_1_die_animation=create_animation(arm_1_textur,Width,3,16,16,(Rectangle){0,48,16,16},8,alloc);
    game_anim->animations->enemies_animation->arm_enemies_animations->arm_1_breathe_animation=arm_1_breathe_animation;
    game_anim->animations->enemies_animation->arm_enemies_animations->arm_1_walk_animation=arm_1_walk_animation;
    game_anim->animations->enemies_animation->arm_enemies_animations->arm_1_attack_animation=arm_1_attack_animation;
    game_anim->animations->enemies_animation->arm_enemies_animations->arm_1_die_animation=arm_1_die_animation;
    //ZOMBIE 0 ANIM
    Texture2D zombie_textur = game_anim->texturs->enemies_texturs->zombie_enemies_textur->zombie_texturs;
    Animation zombie_breathe_animation =create_animation(zombie_textur,Width,4,-25,20,(Rectangle){0,80,25,20},8,alloc);
    Animation zombie_walk_animation =create_animation(zombie_textur,Width,4,-25,20,(Rectangle){0,0,25,20},12,alloc);
    Animation zombie_attack_animation =create_animation(zombie_textur,Width,4,-25,20,(Rectangle){0,20,25,20},8,alloc);
    Animation zombie_die_animation=create_animation(zombie_textur,Width,4,-25,20,(Rectangle){0,40,25,20},8,alloc);
    game_anim->animations->enemies_animation->zombie_enemies_animations->zombie_breathe_animation=zombie_breathe_animation;
    game_anim->animations->enemies_animation->zombie_enemies_animations->zombie_walk_animation=zombie_walk_animation;
    game_anim->animations->enemies_animation->zombie_enemies_animations->zombie_attack_animation=zombie_attack_animation;
    game_anim->animations->enemies_animation->zombie_enemies_animations->zombie_die_animation=zombie_die_animation;

    //ZOMBIEKNIGHT 0 ANIM
    Texture2D knight_zombie_textur = game_anim->texturs->enemies_texturs->knight_zombie_enemies_textur->knight_zombie_texturs;
    Animation knight_zombie_breathe_animation =create_animation(knight_zombie_textur,Width,4,32,32,(Rectangle){0,128,32,32},8,alloc);
    Animation knight_zombie_walk_animation =create_animation(knight_zombie_textur,Width,4,32,32,(Rectangle){0,0,32,32},12,alloc);
    Animation knight_zombie_attack_animation =create_animation(knight_zombie_textur,Width,4,32,32,(Rectangle){0,32,32,32},8,alloc);
    Animation knight_zombie_die_animation=create_animation(knight_zombie_textur,Width,3,32,32,(Rectangle){0,64,32,32},8,alloc);
    game_anim->animations->enemies_animation->knight_zombie_enemies_animations->knight_zombie_breathe_animation=knight_zombie_breathe_animation;
    game_anim->animations->enemies_animation->knight_zombie_enemies_animations->knight_zombie_walk_animation=knight_zombie_walk_animation;
    game_anim->animations->enemies_animation->knight_zombie_enemies_animations->knight_zombie_attack_animation=knight_zombie_attack_animation;
    game_anim->animations->enemies_animation->knight_zombie_enemies_animations->knight_zombie_die_animation=knight_zombie_die_animation;
}
void delete_from_item_anim_queue(GAME_DATA* game_data,GAME_ANIM* game_anim,int id)
{
    if (id > -1)
    {
        bool find_flag = false;
        Animation** queue = game_anim->maps->animation_items_map->animation_map_queue;
        for (int i = 0;i<game_anim->maps->animation_items_map->amount_animation_map_queue;i++)
        {
            if (!find_flag )
            {
                if(queue[i]->index == id)
                {
                    find_flag = true;
                }
            }
            else
            {
                queue[i-1] = queue[i];
            }
        }
        game_anim->maps->animation_items_map->amount_animation_map_queue -=1;
    }
    
}
void append_item_animation(GAME_ANIM* game_anim,int object_type,int textur_type,int object_id)
{
    if (object_type ==EXP)
    {   
        Animation* anim_map = game_anim->maps->animation_items_map->animation_map;
        if (textur_type == small)
        {
            Animation small_exp_anim = game_anim->animations->items_animation->misc_animation->exps_animation->small_exp;
            small_exp_anim.currentFrame = rand_num_within(0,3);

            anim_map[object_id] = small_exp_anim;
            anim_map[object_id].index = object_id;
            anim_map[object_id].isPlaying = true;
            append_item_anim_to_arr(game_anim,&anim_map[object_id]);
        }
        else if (textur_type == medium)
        {
            Animation medium_exp_anim = game_anim->animations->items_animation->misc_animation->exps_animation->medium_exp;
            //pr_int(medium_exp_anim.framesSpeed);
            medium_exp_anim.currentFrame = rand_num_within(0,3);
            anim_map[object_id] = medium_exp_anim;
            anim_map[object_id].index = object_id;
            anim_map[object_id].isPlaying = true;
            append_item_anim_to_arr(game_anim,&anim_map[object_id]);
        }
    }
    else if (object_type ==HEALS)
    {   
        Animation* anim_map = game_anim->maps->animation_items_map->animation_map;
        if (textur_type == small)
        {
            Animation small_heal_anim = game_anim->animations->items_animation->misc_animation->heals_animation->small_heals;
            small_heal_anim.currentFrame = 0;

            anim_map[object_id] = small_heal_anim;
            anim_map[object_id].index = object_id;
            anim_map[object_id].isPlaying = true;
            append_item_anim_to_arr(game_anim,&anim_map[object_id]);
        }
        else if (textur_type == medium)
        {
            Animation medium_heal_anim = game_anim->animations->items_animation->misc_animation->heals_animation->medium_heals;
            //pr_int(medium_exp_anim.framesSpeed);
            medium_heal_anim.currentFrame = 0;
            anim_map[object_id] = medium_heal_anim;
            anim_map[object_id].index = object_id;
            anim_map[object_id].isPlaying = true;
            append_item_anim_to_arr(game_anim,&anim_map[object_id]);
        }
    }
    else if (object_type ==ARMOR_CHEST) 
    {   
        Animation* anim_map = game_anim->maps->animation_items_map->animation_map;
        if (textur_type == 0)
        {
            Animation wooden_armor = game_anim->animations->items_animation->equipment_animation->armors_animation->wooden_armor;
            wooden_armor.currentFrame = 0;

            anim_map[object_id] = wooden_armor;
            anim_map[object_id].index = object_id;
            anim_map[object_id].isPlaying = true;
            append_item_anim_to_arr(game_anim,&anim_map[object_id]);
        }
        else if (textur_type == 1)
        {
            Animation leather_armor = game_anim->animations->items_animation->equipment_animation->armors_animation->leather_armor;
            //pr_int(medium_exp_anim.framesSpeed);
            leather_armor.currentFrame = 0;
            anim_map[object_id] = leather_armor;
            anim_map[object_id].index = object_id;
            anim_map[object_id].isPlaying = true;
            append_item_anim_to_arr(game_anim,&anim_map[object_id]);
        }
        else if (textur_type == 2)
        {
            Animation iron_armor = game_anim->animations->items_animation->equipment_animation->armors_animation->iron_armor;
            //pr_int(medium_exp_anim.framesSpeed);
            iron_armor.currentFrame = 0;
            anim_map[object_id] = iron_armor;
            anim_map[object_id].index = object_id;
            anim_map[object_id].isPlaying = true;
            append_item_anim_to_arr(game_anim,&anim_map[object_id]);
        }
        else if (textur_type == 3)
        {
            Animation mithril_armor = game_anim->animations->items_animation->equipment_animation->armors_animation->mithril_armor;
            //pr_int(medium_exp_anim.framesSpeed);
            mithril_armor.currentFrame = 0;
            anim_map[object_id] = mithril_armor;
            anim_map[object_id].index = object_id;
            anim_map[object_id].isPlaying = true;
            append_item_anim_to_arr(game_anim,&anim_map[object_id]);
        }
    }
    else if (object_type ==WEAPON) 
    {   
        Animation* anim_map = game_anim->maps->animation_items_map->animation_map;
        if (textur_type == 0)
        {
            Animation wooden_armor = game_anim->animations->items_animation->equipment_animation->swords_animation->wooden_weapon;
            wooden_armor.currentFrame = 0;

            anim_map[object_id] = wooden_armor;
            anim_map[object_id].index = object_id;
            anim_map[object_id].isPlaying = true;
            append_item_anim_to_arr(game_anim,&anim_map[object_id]);
        }
        else if (textur_type == 1)
        {
            Animation leather_armor = game_anim->animations->items_animation->equipment_animation->swords_animation->stone_weapon;
            //pr_int(medium_exp_anim.framesSpeed);
            leather_armor.currentFrame = 0;
            anim_map[object_id] = leather_armor;
            anim_map[object_id].index = object_id;
            anim_map[object_id].isPlaying = true;
            append_item_anim_to_arr(game_anim,&anim_map[object_id]);
        }
        else if (textur_type == 2)
        {
            Animation iron_armor = game_anim->animations->items_animation->equipment_animation->swords_animation->iron_weapon;
            //pr_int(medium_exp_anim.framesSpeed);
            iron_armor.currentFrame = 0;
            anim_map[object_id] = iron_armor;
            anim_map[object_id].index = object_id;
            anim_map[object_id].isPlaying = true;
            append_item_anim_to_arr(game_anim,&anim_map[object_id]);
        }
        else if (textur_type == 3)
        {
            Animation mithril_armor = game_anim->animations->items_animation->equipment_animation->swords_animation->mithril_weapon;
            //pr_int(medium_exp_anim.framesSpeed);
            mithril_armor.currentFrame = 0;
            anim_map[object_id] = mithril_armor;
            anim_map[object_id].index = object_id;
            anim_map[object_id].isPlaying = true;
            append_item_anim_to_arr(game_anim,&anim_map[object_id]);
        }
    }
    else if (object_type ==HELMET) 
    {   
        Animation* anim_map = game_anim->maps->animation_items_map->animation_map;
        if (textur_type == 0)
        {
            Animation wooden_armor = game_anim->animations->items_animation->equipment_animation->helmets_animation->wooden_HELMET;
            wooden_armor.currentFrame = 0;

            anim_map[object_id] = wooden_armor;
            anim_map[object_id].index = object_id;
            anim_map[object_id].isPlaying = true;
            append_item_anim_to_arr(game_anim,&anim_map[object_id]);
        }
        else if (textur_type == 1)
        {
            Animation leather_armor = game_anim->animations->items_animation->equipment_animation->helmets_animation->leather_HELMET;
            //pr_int(medium_exp_anim.framesSpeed);
            leather_armor.currentFrame = 0;
            anim_map[object_id] = leather_armor;
            anim_map[object_id].index = object_id;
            anim_map[object_id].isPlaying = true;
            append_item_anim_to_arr(game_anim,&anim_map[object_id]);
        }
        else if (textur_type == 2)
        {
            Animation iron_armor = game_anim->animations->items_animation->equipment_animation->helmets_animation->iron_HELMET;
            //pr_int(medium_exp_anim.framesSpeed);
            iron_armor.currentFrame = 0;
            anim_map[object_id] = iron_armor;
            anim_map[object_id].index = object_id;
            anim_map[object_id].isPlaying = true;
            append_item_anim_to_arr(game_anim,&anim_map[object_id]);
        }
        else if (textur_type == 3)
        {
            Animation mithril_armor = game_anim->animations->items_animation->equipment_animation->helmets_animation->mithril_HELMET;
            //pr_int(medium_exp_anim.framesSpeed);
            mithril_armor.currentFrame = 0;
            anim_map[object_id] = mithril_armor;
            anim_map[object_id].index = object_id;
            anim_map[object_id].isPlaying = true;
            append_item_anim_to_arr(game_anim,&anim_map[object_id]);
        }
    }
    /*
    if (object_type ==COINS)
    {   
        Animation* anim_map = game_anim->maps->animation_items_map->animation_map;
        if (textur_type == small)
        {
            Animation small_exp_anim = game_anim->animations->items_animation->misc_animation->exps_animation->small_exp;
            small_exp_anim.currentFrame = rand_num_within(0,3);

            anim_map[object_id] = small_exp_anim;
            anim_map[object_id].index = object_id;
            append_item_anim_to_arr(game_anim,&anim_map[object_id]);
        }
        else if (textur_type == medium)
        {
            Animation medium_exp_anim = game_anim->animations->items_animation->misc_animation->exps_animation->medium_exp;
            //pr_int(medium_exp_anim.framesSpeed);
            medium_exp_anim.currentFrame = rand_num_within(0,3);
            anim_map[object_id] = medium_exp_anim;
            append_item_anim_to_arr(game_anim,&anim_map[object_id]);
        }
    }
        */
}
void update_ememies_animations(GAME_ANIM* game_anim)
{
    Animation*** anim_enemy_list = game_anim->maps->animation_enemies_map->animation_map_queue;
    int* amount = &game_anim->maps->animation_enemies_map->amount_animation_map_queue;
    for (int i =0;i<*amount;i++)
    {
    
        //pr_int(*amount);
        //pr_int(anim_enemy_list[i]->frameCount);
        //pr_int(anim_enemy_list[i]->framesCounter);
        update_animation(anim_enemy_list[i][0]);
        //pr_int(anim_enemy_list[i]->texture.id);
        //pr_int(anim_enemy_list[i]->cur_frameRec.x);
    }
}

void append_to_anim_enemy_list_updater(GAME_DATA* game_data,GAME_ANIM* game_anim,Enemy* enemy)
{
    if (enemy->current_animation != NULL)
    {
        //pr_int(444);   
        Animation*** anim_enemy_list = game_anim->maps->animation_enemies_map->animation_map_queue;
        int* amount = &game_anim->maps->animation_enemies_map->amount_animation_map_queue;
        anim_enemy_list[*amount] = enemy->current_animation;
        
        *amount+=1;
    }
    
}