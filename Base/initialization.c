#include "initialization.h"




bool GAME_INIT(GAME_DATA* game_data,int tilesX, int tilesY, int tileSize,GAME_ANIM* game_anim)
{
    window_init(game_data);
    structurs_init(game_data,game_anim,tilesX,  tilesY,  tileSize);
    cave_init(game_data);
    spawn_pos_init(game_data);
    map_objects_init(game_data);
    items_init(game_data,game_anim);
    enemy_init(game_data,game_anim);
    fog_init(game_data);
    player_review(game_data);
    enemies_finding(game_data);
}

bool window_init(GAME_DATA* game_data)
{
    InitWindow(800,600,"tishanooboos");
    
    //ToggleFullscreen();
    int monitor_width = GetScreenWidth();
    int monitor_height = GetScreenHeight();
    
    SetTargetFPS(60);
    game_data->misc->monitor_size.monitor_width = monitor_width;
    game_data->misc->monitor_size.monitor_height = monitor_height;
    
    return true;
}

bool anim_speed_init(GAME_DATA* game_data,float player_speed_move)
{
    
}

bool structurs_init(GAME_DATA* game_data,GAME_ANIM* game_anim,int tilesX, int tilesY, int tileSize)
{
    texturs_init(game_anim);
    anim_init(game_anim);
    create_animations(game_data,game_anim);
    player_init( game_data);
    player_anim_init(game_data,game_anim);
    append_player_anim_to_arr(game_anim,game_data->player->current_anim);
    cells_map_init(game_data, tilesX,  tilesY,  tileSize);
    collision_map_init(game_data);
    pos_map_init(game_data);
    camera_init(game_data);
    enemy_map_init(game_data); 
    path_init(game_data);
    items_map_init(game_data);
    

    return true;

}
void anim_init(GAME_ANIM* game_anim)
{
    game_anim->animations = create_animations_struct(game_anim->anim_alloc);
}

bool path_init(GAME_DATA* game_data)
{
    int tilesX = game_data->maps->cells_map->tilesX;
    int tilesY = game_data->maps->cells_map->tilesY;
    Path* path = create_path_structur(game_data->allocators->alloc_misc,tilesX,tilesY);
    game_data->misc->path = path; 
    return true;
}
bool items_map_init(GAME_DATA* game_data)
{
    int tilesX = game_data->maps->cells_map->tilesX;
    int tilesY = game_data->maps->cells_map->tilesY;
    ItemsMap* map = create_items_map(game_data->allocators->alloc_data,tilesX,tilesY);
    game_data->maps->items_map = map;
}

bool allcator_init(GAME_DATA* game_data)
{
    
}

bool player_init(GAME_DATA* game_data)
{
    Player* player = create_player(game_data->allocators->alloc_data,game_data->misc->monitor_size.monitor_width/2,game_data->misc->monitor_size.monitor_height/2);
    game_data->player = player;
    return true;
}

bool cells_map_init(GAME_DATA* game_data,int tilesX, int tilesY, int tileSize)
{
    CellsMap* cells_map = create_cells_map(game_data->allocators->alloc_data,tilesX,tilesY,tileSize);
    
    game_data->maps->cells_map = cells_map;
    raw_initialization_cells(game_data->allocators->alloc_data,game_data->maps->cells_map);
    return true;
}

bool camera_init(GAME_DATA* game_data)
{
    Camera2D camera = { 0 };
    camera.target = game_data->player->player_pos->position_pixels->pos_pixels;;
    camera.offset = (Vector2){ game_data->misc->monitor_size.monitor_width/2.0f, game_data->misc->monitor_size.monitor_height/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    game_data->misc->camera = camera;
    return true;
}

bool spawn_pos_init(GAME_DATA* game_data)
{
    int dx[] = {0,0,1,1,1,0,-1,-1,-1};
    int dy[] = {0,-1,-1,0,1,1,1,0,-1};

    char** map = game_data->maps->collision_map->grid;

    int tilesX = game_data->maps->cells_map->tilesX;
    int tilesY = game_data->maps->cells_map->tilesY;
    int start_tile_x = rand_num_within((int)(tilesX*0.4),(int)(tilesX*0.6));
    int start_tile_y = rand_num_within((int)(tilesY*0.4),(int)(tilesY*0.6));
    
    for (int i = 0;i<9;i++)
    {
        map[start_tile_x+dx[i]][start_tile_y+dy[i]] = 'f';
    }
    game_data->maps->collision_map->grid[start_tile_x][start_tile_y] = 'p';
    Vector2 start_pos_tiles = {start_tile_x,start_tile_y};
    Vector2 start_pos_pixels = {game_data->maps->cells_map->cells[start_tile_x][start_tile_y]->positin.x+game_data->maps->cells_map->tileSize/2,game_data->maps->cells_map->cells[start_tile_x][start_tile_y]->positin.y+game_data->maps->cells_map->tileSize/2};
    game_data->player->player_pos->position_pixels->pos_pixels = start_pos_pixels;
    game_data->player->player_pos->position_tiles->pos_tiles = start_pos_tiles;

    return true;
}

bool collision_map_init(GAME_DATA* game_data)
{

    CollisionMap* map = create_collision_map(game_data->allocators->alloc_data,game_data->maps->cells_map->tilesX,game_data->maps->cells_map->tilesY);
    game_data->maps->collision_map = map;
}
bool pos_map_init(GAME_DATA* game_data)
{

    ActionsMap* map = create_action_map(game_data->allocators->alloc_data);
    game_data->maps->actins_map = map;
}
bool fog_init(GAME_DATA* game_data)
{
    FogMap* fog_map = create_fog_map(game_data->allocators->alloc_data,game_data->maps->cells_map->tilesX,game_data->maps->cells_map->tilesY);
    game_data->maps->fog_map = fog_map;
    map_in_fog(game_data);

}

bool cave_init(GAME_DATA* game_data)
{
    generate_cave_cellular_smoothing(game_data);

}

bool map_objects_init(GAME_DATA* game_data)
{

    char** collision_map = game_data->maps->collision_map->grid;
    CellsMap* objects_map = game_data->maps->cells_map;

    int tilesX = game_data->maps->cells_map->tilesX;
    int tilesY = game_data->maps->cells_map->tilesY;
    for (int x = 0; x < tilesX; x++)
    {
        for (int y = 0; y < tilesY; y++)
        {
            if (collision_map[x][y] == 'f')
            {
                char* floor_t = textur(floor_textur,-1);
                objects_map->cells[x][y]->objects[0] = floor_t;
            }
            else if (collision_map[x][y] == 'w')
            {
                char* wall_t = textur(wall_textur,-1);
                objects_map->cells[x][y]->objects[0] = wall_t;
            }
            else if (collision_map[x][y] == 'p')
            {
                char* floor_t = textur(floor_textur,-1);
                objects_map->cells[x][y]->objects[0] = floor_t;
                objects_map->cells[x][y]->objects[1] = textur(player_textur,-1);
            }
            else if (collision_map[x][y] == 'b')
            {
                char* wall_t = textur(wall_textur,-1);
                objects_map->cells[x][y]->objects[0] = wall_t;
            }
        }
    }
    //print_objects_map(game_data);
}

bool enemy_map_init(GAME_DATA* game_data)
{
    EnemyMap* map = create_enemy_map(game_data->allocators->alloc_misc,10,game_data->maps->cells_map->tilesX,game_data->maps->cells_map->tilesY);
    game_data->maps->enemy_map = map;
}

bool enemy_init(GAME_DATA* game_data,GAME_ANIM* game_anim)
{
    int posX = game_data->player->player_pos->position_tiles->pos_tiles.x;
    int posY = game_data->player->player_pos->position_tiles->pos_tiles.y;

    spawn_enemy(game_anim,game_data,posX+1,posY-1,enemy_indexes,1,-1);
     spawn_enemy(game_anim,game_data,posX+1,posY,enemy_indexes,0,1);
   // spawn_enemy(game_anim,game_data,posX+1,posY+1,enemy_indexes,0,1);
   // spawn_enemy(game_anim,game_data,posX-1,posY-1,enemy_indexes,0,0);
  //  spawn_enemy(game_anim,game_data,posX-1,posY+1,enemy_indexes,0,0);
    //spawn_enemy(game_anim,game_data,posX+1,posY-1,enemy_indexes,0,0);
    
   //enemies_rand_spawn(game_data,game_anim);

                
}
bool items_init(GAME_DATA* game_data,GAME_ANIM* game_anim)
{   
    int posX = game_data->player->player_pos->position_tiles->pos_tiles.x;
    int posY = game_data->player->player_pos->position_tiles->pos_tiles.y;




    //spawn_item(game_data,posX-1,posY-1,textur(ARMOR_CHEST,2));
    equipments_rand_spawn(game_data,game_anim);

}