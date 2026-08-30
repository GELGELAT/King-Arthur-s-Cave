#include "RendererActionsTiles.h"

void actions_glow_tiles_draw(GAME_DATA* game_data,GAME_ANIM* game_anim)
{
    char** map = game_data->maps->actins_map->tiles_glow;
    int tilesX = game_data->maps->cells_map->tilesX;
    int tilesY = game_data->maps->cells_map->tilesY;
    for (int x=0;x<tilesX;x++)
    {
        for(int y=0;y<tilesY;y++)
        {
            if (map[y][x]>='1' &&map[y][x]<='4' )
            {
                Vector2 pos_1 = game_data->maps->cells_map->cells[y][x]->positin;
                draw_animation(&game_anim->animations->world_animation->tiles_animation->action_tiles_animations->tiles_backlight_animation,
                pos_1,64,64,4,0,(Color){ 255, 255, 255, 40 });
            }
            if (map[y][x]=='1')
            {
                Vector2 pos_1 = game_data->maps->cells_map->cells[y][x]->positin;
                draw_animation(&game_anim->animations->world_animation->tiles_animation->action_tiles_animations->tiles_backlight_glow_effect_animation_1,
                pos_1,64,64,4,0,(Color){ 255, 255, 255, 128 });
            }
            else if (map[y][x]=='2')
            {
                Vector2 pos_1 = game_data->maps->cells_map->cells[y][x]->positin;
                draw_animation(&game_anim->animations->world_animation->tiles_animation->action_tiles_animations->tiles_backlight_glow_effect_animation_2,
                pos_1,64,64,4,0,(Color){ 255, 255, 255, 128 });
            }
            else if (map[y][x]=='3')
            {
                Vector2 pos_1 = game_data->maps->cells_map->cells[y][x]->positin;
                draw_animation(&game_anim->animations->world_animation->tiles_animation->action_tiles_animations->tiles_backlight_glow_effect_animation_3,
                pos_1,64,64,4,0,(Color){ 255, 255, 255, 128 });
            }
            else if (map[y][x]=='4')
            {
                Vector2 pos_1 = game_data->maps->cells_map->cells[y][x]->positin;
                draw_animation(&game_anim->animations->world_animation->tiles_animation->action_tiles_animations->tiles_backlight_glow_effect_animation_4,
                pos_1,64,64,4,0,(Color){ 255, 255, 255, 128 });
            }
            if (map[y][x]>='1' &&map[y][x]<='4' )
            {
                Vector2 pos_1 = game_data->maps->cells_map->cells[y][x]->positin;
                draw_animation(&game_anim->animations->world_animation->tiles_animation->action_tiles_animations->tiles_backlight_line_animation_1,
                pos_1,64,64,4,0,(Color){ 255, 255, 255, 255 });
            }
        }
    }
}