#include "ActionsTilesLogic.h"

Vector2 actions_tiles_glow_plus_one[4] = {{0,-1},{1,0},{0,1},{-1,0}};
int actions_tiles_glow_plus_one_amount = 4;




void actions_mark_tiles(GAME_DATA* game_data,Vector2 current_pos,Vector2* mark_increments,int amount_increments)
{
    char** tiles_map = game_data->maps->actins_map->tiles_glow;
    for (int i=0;i<amount_increments;i++)
    {
        Vector2 current_mark_tile = vector_sum(current_pos,mark_increments[i]);
        
        int current_mark_tile_x = current_mark_tile.x;
        int current_mark_tile_y = current_mark_tile.y;
        int rand_textur = rand_num_within(1,4);
        tiles_map[current_mark_tile_x][current_mark_tile_y] = '0' + rand_textur;
    }

}

void actions_clear_mark_tiles(GAME_DATA* game_data)
{
    char** tiles_map = game_data->maps->actins_map->tiles_glow;

    for (int i =0;i<game_data->maps->cells_map->tilesX;i++)
    {
        for (int j =0;j<game_data->maps->cells_map->tilesY;j++)
        {
            tiles_map[i][j] = '0';
        }
    }
}
bool actions_mouse_click_check(GAME_DATA* game_data,Vector2 mouse_click)
{
    int mouse_click_x = mouse_click.x;
    int mouse_click_y = mouse_click.y;
    char** tiles_map = game_data->maps->actins_map->tiles_glow;
    print_char_map(game_data,tiles_map);
    if (tiles_map[mouse_click_x][mouse_click_y]>='1' &&tiles_map[mouse_click_x][mouse_click_y]<='4' )
    {
        return true;
    }
    else
    {
        return false;
    }
}
void init_actions_tiles_queue(GAME_DATA* game_data,GAME_ANIM* game_anim)
{
    Animation**queue = game_anim->maps->animation_world_maps->animation_action_tiles_map->animation_action_tiles_map_queue;
    queue[0] =&game_anim->animations->world_animation->tiles_animation->action_tiles_animations->tiles_backlight_animation;
    queue[1] =&game_anim->animations->world_animation->tiles_animation->action_tiles_animations->tiles_backlight_glow_effect_animation_1;
    queue[2] =&game_anim->animations->world_animation->tiles_animation->action_tiles_animations->tiles_backlight_glow_effect_animation_2;
    queue[3] =&game_anim->animations->world_animation->tiles_animation->action_tiles_animations->tiles_backlight_glow_effect_animation_3;
    queue[4] =&game_anim->animations->world_animation->tiles_animation->action_tiles_animations->tiles_backlight_glow_effect_animation_4;

    queue[5] =&game_anim->animations->world_animation->tiles_animation->action_tiles_animations->tiles_backlight_line_animation_1;
    queue[6] =&game_anim->animations->world_animation->tiles_animation->action_tiles_animations->tiles_backlight_line_animation_2;
    queue[7] =&game_anim->animations->world_animation->tiles_animation->action_tiles_animations->tiles_backlight_line_animation_3;
    queue[8] =&game_anim->animations->world_animation->tiles_animation->action_tiles_animations->tiles_backlight_line_animation_4;

    game_anim->maps->animation_world_maps->animation_action_tiles_map->amount_animation_action_tiles_map_queue = 9;
}