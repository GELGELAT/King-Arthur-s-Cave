#include "structurs.h"

int enemy_indexes = 0;
Player* create_player(Allocator* alloc,int start_posX,int start_posY)
{
    Player* player = alloc_alloc(alloc,sizeof(Player));
    PlayerExp* player_exp = alloc_alloc(alloc,sizeof(PlayerExp));
    player_exp->experience_points = 0;
    player_exp->level = 0;
    PlayerCoins* player_coins = alloc_alloc(alloc,sizeof(PlayerCoins));
    player_coins->coins = 0;
    PlayerEquipmentTier* player_equipment_tier = alloc_alloc(alloc,sizeof(PlayerEquipmentTier));
    player_equipment_tier->armor_tier = 0;
    player_equipment_tier->HELMET_tier = 0;
    player_equipment_tier->sword_tier = 0;
    PlayerCharacteristics* player_characteristics = alloc_alloc(alloc,sizeof(PlayerCharacteristics));
    player_characteristics->defense = 0;
    player_characteristics->heal_points = 100;
    player_characteristics->max_physical_damage = 100;
    player_characteristics->min_physical_damage = 50;
    PlayerStats* player_stats = alloc_alloc(alloc,sizeof(PlayerStats));
    player_stats->player_characteristics =player_characteristics;
    player_stats->player_coins =player_coins;
    player_stats->player_equipment_tier = player_equipment_tier;
    player_stats->player_exp = player_exp;
    PlayerTilesPos* player_tiles_pos = alloc_alloc(alloc,sizeof(PlayerTilesPos));
    player_tiles_pos->pos_tiles = (Vector2){-1,-1};
    PlayerPixelsPos* player_pixels_pos = alloc_alloc(alloc,sizeof(PlayerPixelsPos));
    player_pixels_pos->pos_pixels = (Vector2){-1,-1};
    PlayerPos* player_pos = alloc_alloc(alloc,sizeof(PlayerPos));
    player_pos->position_pixels =player_pixels_pos;
    player_pos->position_tiles = player_tiles_pos;

    player->player_stats = player_stats;
    player->player_pos = player_pos;
    PlayerAnimations* player_anim = alloc_alloc(alloc,sizeof(PlayerAnimations));
    player->player_anim =player_anim;
    PlayerBodyPos  * body_pos = alloc_alloc(alloc,sizeof(PlayerBodyPos  ));
    player->body_pos=body_pos;
    player->current_anim = alloc_alloc(alloc,sizeof(Animation*));


    
    player->current_anim[0] = &player->player_anim->player_breathe_animation;
    player->player_anim->size_x =96;
    player->player_anim->size_y =96;
    player->player_anim->alignment_x = 48;
    player->player_anim->alignment_y = 60;
    return player;
}

ActionsMap* create_action_map(Allocator* alloc)
{
    ActionsMap* actions_map = alloc_alloc(alloc,sizeof(ActionsMap));
    Action**actions_main_queue= alloc_alloc(alloc,sizeof(Action*)*100);
    Action**actions_effects_queue= alloc_alloc(alloc,sizeof(Action*)*100);
    actions_map->actions_main_queue=actions_main_queue;
    actions_map->actions_effects_queue =actions_effects_queue;
    actions_map->amount_actions_effects_queue=0;
    actions_map->amount_actions_main_queue=0;
    return actions_map;
}

Action* create_action(Allocator* alloc,int flow,int object_type,int object_index,int movement_type ,int action_type ,int during_type,int affected_type,int affected_index,
    Vector2* position_pixels,Vector2 old_tile,Vector2 new_tile,float max_fill,float speed)
{
    Action* action = alloc_alloc(alloc,sizeof(Action));
    action->flow = flow;
    ActionMainInfo*main =alloc_alloc(alloc,sizeof(ActionMainInfo));
    action->main =main;
    action->main->action_type =action_type;
    action->main->during_type =during_type;
    action->main->movement_type =movement_type;
    ActionMiscInfo *misc =alloc_alloc(alloc,sizeof(ActionMiscInfo));
    action->misc=misc;
    action->misc->current_fill=0;
    action->misc->current_state=0;
    action->misc->max_fill=max_fill;
    action->misc->speed=speed;
    ActionObjectInfo*object =alloc_alloc(alloc,sizeof(ActionObjectInfo));
    action->object=object;
    action->object->object_index =object_index;
    action->object->object_type =object_type;
    action->object->affected_type=affected_type;
    action->object->affected_index =affected_index;
    ActionPos *pos =alloc_alloc(alloc,sizeof(ActionPos));
    action->pos=pos;
    action->pos->position_pixels =position_pixels;
    action->pos->old_tile=old_tile;
    action->pos->new_tile=new_tile;
    ActionQueueInfo *queue =alloc_alloc(alloc,sizeof(ActionQueueInfo));
    action->queue=queue;
    action->queue->beginning_action= NULL;
    action->queue->ending_action =NULL;
    return action;
}

GAME_DATA* create_game_data()
{
    Allocator* alloc = create_alloc(1024*1024);
    
    Allocator* alloc_path = create_alloc(1024*1024);
   
    GAME_DATA* game_data = alloc_alloc(alloc,sizeof(GAME_DATA));
    Maps* maps = alloc_alloc(alloc,sizeof(Maps));
    Allocators* allocs = alloc_alloc(alloc,sizeof(Allocators));
    Misc* misc = alloc_alloc(alloc,sizeof(Misc));
    
    game_data->maps = maps;
    game_data->allocators = allocs;
    game_data->misc = misc;
    game_data->allocators->alloc_data = alloc; 
    game_data->allocators->alloc_misc = alloc_path; 
    
    return game_data;
}

AnimationEnemyMap* create_anim_enemies_map(GAME_ANIM* game_anim)
{
    AnimationEnemyMap* enemy_map = alloc_alloc(game_anim->anim_alloc,sizeof(AnimationEnemyMap));
    enemy_map->animation_map_queue = alloc_alloc(game_anim->anim_alloc,sizeof(Animation**)*1000);
    enemy_map->amount_animation_map_queue = 0;
    return enemy_map;

}
AnimationPlayerMap* create_anim_player_map(GAME_ANIM* game_anim)
{
    AnimationPlayerMap* player_map = alloc_alloc(game_anim->anim_alloc,sizeof(AnimationPlayerMap));
    player_map->animation_map_queue = alloc_alloc(game_anim->anim_alloc,sizeof(Animation**)*5);
    player_map->amount_animation_map_queue = 0;
    return player_map;

}
AnimationItemsMap* create_anim_items_map(GAME_ANIM* game_anim)
{
    AnimationItemsMap* items_map = alloc_alloc(game_anim->anim_alloc,sizeof(AnimationItemsMap));
    items_map->animation_map = alloc_alloc(game_anim->anim_alloc,sizeof(Animation)*1000);
    items_map->animation_map_queue = alloc_alloc(game_anim->anim_alloc,sizeof(Animation*)*1000);
    items_map->amount_animation_map_queue = 0;
    return items_map;

}
GAME_ANIM* create_game_anim()
{
    Allocator* alloc = create_alloc(1024*1024);
    GAME_ANIM* game_anim = alloc_alloc(alloc,sizeof(GAME_ANIM));
    Animations* animations = alloc_alloc(alloc,sizeof(Animations));
    Texturs* texturs = alloc_alloc(alloc,sizeof(Texturs));
    AnimationMaps* maps = alloc_alloc(alloc,sizeof(AnimationMaps));
    
    game_anim->anim_alloc =alloc;
    AnimationItemsMap* items_map = create_anim_items_map(game_anim);
    game_anim->animations = animations;
    game_anim->texturs = texturs;
    game_anim->maps = maps;
    game_anim->maps->animation_items_map = items_map;
    game_anim->maps->animation_enemies_map = create_anim_enemies_map(game_anim);
    game_anim->maps->animation_player_map=create_anim_player_map(game_anim);
    return game_anim;
}

ItemsMap* create_items_map(Allocator* alloc,int tilesX, int tilesY)
{
    ItemsMap* map = alloc_alloc(alloc,sizeof(ItemsMap));
    map->index_map = alloc_alloc(alloc,sizeof(int*)*tilesX);
    map->items_map = alloc_alloc(alloc,sizeof(Item*)*tilesX*tilesX);
    map->items_map_amount = 0;
    for (int x =0;x<tilesX;x++)
    {
        map->index_map[x] = alloc_alloc(alloc,sizeof(int)*tilesY);
        for (int y = 0; y<tilesY;y++)
        {
            map->index_map[x][y] = -1;
        }
    }
    return map;
}
Cell* create_cell(Allocator* alloc)
{
    Cell* cell = alloc_alloc(alloc, sizeof(Cell));
    if (cell == NULL)
    {
        printf("error no memory for mainmap3");
        return NULL;
    }
    cell->objects = (char**)alloc_alloc(alloc, sizeof(char*)*4);
    if (cell->objects == NULL)
    {
        printf("error no memory for mainmap3");
        return NULL;
    }
    return cell;
}

FogMap* create_fog_map(Allocator* alloc,int tilesX, int tilesY)
{
    FogMap* map = alloc_alloc(alloc,sizeof(FogMap));
    map->grid = (alloc_alloc(alloc,sizeof(char*)*tilesX));
    for (int x =0;x<tilesX;x++)
    {
        map->grid[x] = (char*)(alloc_alloc(alloc,sizeof(char)*tilesY));
        for (int y = 0; y<tilesY;y++)
        {
            map->grid[x][y] = 'f';
        }
    }
    return map;
}

CellsMap* create_cells_map(Allocator* alloc,int tilesX, int tilesY, int tileSize)
{
    CellsMap* object = alloc_alloc(alloc,sizeof(CellsMap));
    if (object == NULL)
    {
        printf("error no memory for mainmap1");
        return NULL;
    }
    object->tilesX = tilesX;
    object->tilesY = tilesY;
    object->tileSize = tileSize;
    object->cells = (Cell***)(alloc_alloc(alloc,tilesX*sizeof(Cell**)));
    if (object->cells == NULL)
    {
        printf("error no memory for mainmap2");
        return NULL;
    }
    for (int x = 0;x<tilesX;x++)
    {
        object->cells[x] = (Cell**)(alloc_alloc(alloc,tilesY*sizeof(Cell*)));
        
        if (object->cells[x] == NULL)
        {
            printf("error no memory for mainmap3");
            return NULL;
        }
        for (int y = 0; y< tilesY;y++)
        {
            object->cells[x][y] = create_cell(alloc);
            Vector2 pos = {x*tileSize,y*tileSize};
            object->cells[x][y]->positin = pos;
            if (object->cells[x][y] == NULL)
            {
                printf("error no memory for mainmap4");
                return NULL;
            }
        }
    }
    return object;
}

CollisionMap* create_collision_map(Allocator* alloc,int tilesX, int tilesY)
{
    CollisionMap* collision_map = alloc_alloc(alloc,sizeof(CollisionMap));
    collision_map->tilesX = tilesX;
    collision_map->tilesY = tilesY;
    collision_map->grid = (char**)(alloc_alloc(alloc,sizeof(char*)*tilesX));
    for (int x =0;x<tilesX;x++)
    {
        collision_map->grid[x] = (char*)(alloc_alloc(alloc,sizeof(char)*tilesY));
        for (int y = 0; y<tilesY;y++)
        {
            collision_map->grid[x][y] = 'f';
        }
    }
    return collision_map;
}



EnemyMap* create_enemy_map(Allocator* alloc,int enemy_indexes,int tilesX,int tilesY)
{
    EnemyMap* enemy_map = alloc_alloc(alloc,sizeof(EnemyMap));
    enemy_map->enemy_map = alloc_alloc(alloc,sizeof(Enemy*)*100);
    enemy_map->move_queue = alloc_alloc(alloc,sizeof(Enemy*)*100);
    enemy_map->move_queue_amount = 0;
    enemy_map->enemy_map_amount = 0;

    enemy_map->index_map = alloc_alloc(alloc,sizeof(int*)*tilesX);
    for (int x = 0;x<tilesX;x++)
    {
        enemy_map->index_map[x] = alloc_alloc(alloc,sizeof(int)*tilesY);
        for (int y = 0;y<tilesY;y++)
        {
            enemy_map->index_map[x][y] = -1;
        }
    }
    return enemy_map;

}



void raw_initialization_cells(Allocator* alloc,CellsMap* cells_map)
{
    int tile_size = cells_map->tileSize;
    int tilesX = cells_map->tilesX;
    int tilesY = cells_map->tilesY;
    //char** objects = alloc_alloc(alloc,sizeof(char*));
    int amount = 1;
    for (int x = 0; x<tilesX;x++)
    {
        for (int y = 0; y<tilesY;y++)
        {
            Vector2 positin = {x*tile_size,y*tile_size};
            cells_map->cells[x][y]->positin = positin;
            


            //cells_map->cells[x][y]->objects = &objects;
            cells_map->cells[x][y]->amount_objects = amount;
        }
    }

}

Path* create_path_structur(Allocator* alloc,int tilesX,int tilesY)
{
    Path* path = alloc_alloc(alloc,sizeof(Path));
    path->parents_position_tiles = alloc_alloc(alloc,tilesX*sizeof(Vector2*));
    path->visited_tiles = alloc_alloc(alloc,tilesX*sizeof(char*));
    for (int x = 0; x<tilesX;x++)
    {
        path->parents_position_tiles[x] = alloc_alloc(alloc,sizeof(Vector2)*tilesY);
        path->visited_tiles[x] = alloc_alloc(alloc,sizeof(char)*tilesY);
        for (int y = 0; y<tilesY;y++)
        {
            Vector2 z = {0,0};
            path->parents_position_tiles[x][y] = z;
            path->visited_tiles[x][y] = '0';
        }
    }
    return path;
}