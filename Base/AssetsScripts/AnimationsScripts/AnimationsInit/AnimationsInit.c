#include "AnimationsInit.h"


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

    //PLAYER HUMAN ANIM
    Texture2D player_human_textur = game_anim->texturs->player_texturs->player_human->human_textur;
    Animation player_human_breathe_animation =create_animation(player_human_textur,Width,4,-32,32,(Rectangle){96,96,-32,32},8,alloc);
    Animation player_human_walk_animation =create_animation(player_human_textur,Width,4,-32,32,(Rectangle){128,0,-32,32},12,alloc);
    Animation player_human_attack_animation =create_animation(player_human_textur,Width,3,-32,32,(Rectangle){160,32,-32,32},8,alloc);
    //Animation player_human_die_animation=create_animation(player_human_textur,Width,4,-32,32,(Rectangle){0,40,32,32},8,alloc);
    Animation player_human_mine_animation=create_animation(player_human_textur,Width,5,-32,32,(Rectangle){128,64,-32,32},8,alloc);

    game_anim->animations->player_animation->human_animations->player_breathe_animation =player_human_breathe_animation;
    game_anim->animations->player_animation->human_animations->player_attack_animation =player_human_attack_animation;
    //game_anim->animations->player_animation->human_animations->player_die_animation =player_human_die_animation;
    game_anim->animations->player_animation->human_animations->player_mine_animation =player_human_mine_animation;
    game_anim->animations->player_animation->human_animations->player_walk_animation =player_human_walk_animation;
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

    PlayersAnimations * player_animation = alloc_alloc(alloc,sizeof(PlayersAnimations ));
    HumanAnimations * human_animations = alloc_alloc(alloc,sizeof(HumanAnimations ));
    animation->player_animation=player_animation;
    animation->player_animation->human_animations =human_animations;
    

    
    return animation;
}

void player_anim_init(GAME_DATA* game_data,GAME_ANIM* game_anim)
{
    Player* player = game_data->player;
    player->player_anim->player_breathe_animation = game_anim->animations->player_animation->human_animations->player_breathe_animation;
    player->player_anim->player_walk_animation = game_anim->animations->player_animation->human_animations->player_walk_animation;
    player->player_anim->player_attack_animation =game_anim->animations->player_animation->human_animations->player_attack_animation;
    player->player_anim->player_mine_animation = game_anim->animations->player_animation->human_animations->player_mine_animation;
}