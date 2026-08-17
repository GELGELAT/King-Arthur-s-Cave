#include "TextursLogic.h"

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