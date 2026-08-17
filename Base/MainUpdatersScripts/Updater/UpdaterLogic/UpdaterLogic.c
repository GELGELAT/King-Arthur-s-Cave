#include "UpdaterLogic.h"

void GAME_UPDATE(GAME_DATA *game_data,GAME_ANIM* game_anim)
{
    pos_player_updater(game_data,game_anim);
    camera_updater(game_data);
    main_action_map_updater(game_data,game_anim);
    update_items_animations(game_anim);
    update_ememies_animations(game_anim);
    update_player_animations(game_anim);
}
