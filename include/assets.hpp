#include "raylib.h"
#pragma once

struct assets_manager
{
    //textures
    Texture2D player_sprite_idle;
    Texture2D player_sprite_run;
    Texture2D player_sprite_jump;
    Texture2D grass;
    Texture2D spike;
    Texture2D box;
    Texture2D ladder;
    Texture2D goal;
    Texture2D background1;
    Texture2D background2;

    // Sounds
    Sound player_walk;
    Sound player_jump;
    Sound enemy_sound;
    Sound coin_pickup;
    Sound menu_switch;
    Music ui_music;
    Music gameplay_music_1;
    Music gameplay_music_2;
    Music gameplay_music_3;
    Music gameplay_music_4;

    // Constructor & Destructor
    assets_manager();
    ~assets_manager();
};
