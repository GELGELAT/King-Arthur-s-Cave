#include "UpdaterCamera.h"

void camera_updater(GAME_DATA *game_data)
{
    game_data->misc->camera.offset = (Vector2){ game_data->misc->monitor_size.monitor_width/2.0f, game_data->misc->monitor_size.monitor_height/2.0f };
    game_data->misc->camera.target = game_data->player->player_pos->position_pixels->pos_pixels;;
}
