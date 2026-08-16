#include <stdlib.h> 
#include "raylib.h"

#include "structurs.h"

#include "Allocator.h"
#include "updater.h"
#include "renderer.h"
#include "initialization.h"
#include "structurs.h"
#include <stdio.h>
#include <time.h>




int main(void)
{
    srand((unsigned int)time(NULL));
    GAME_DATA* game_data = create_game_data();
    GAME_ANIM* game_anim = create_game_anim();
    GAME_INIT(game_data,50,50,64,game_anim);
    while (!WindowShouldClose())
    {
        GAME_UPDATE(game_data,game_anim);

        BeginDrawing();
            BeginMode2D(game_data->misc->camera);
                ClearBackground(WHITE);
                GAME_DRAW(game_data,game_anim);
            EndMode2D();

        EndDrawing();
    }
    CloseWindow();
    
}

