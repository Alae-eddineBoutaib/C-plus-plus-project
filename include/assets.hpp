#include "raylib.h"
#pragma once

struct assets_manager
{
    //textures
    Texture2D player_sprite_idle;
    Texture2D player_sprite_run;
    Texture2D player_sprite_jump;
    Texture2D enemy_1;
    Texture2D enemy_2;
    Texture2D enemy_3;
    Texture2D box;

    // Sounds
    Sound player_walk;
    Sound player_jump;
    Sound enemy_sound;
    Sound coin_pickup;

    // Constructor & Destructor
    assets_manager();
    ~assets_manager();
};
