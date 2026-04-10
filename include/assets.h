#include "raylib.h"

struct assets_manager
{
    //textures
    Texture2D player_sprite;
    Texture2D ghost_sprite;
    Texture2D skeleton_sprite;
    Texture2D robot_sprite;

    // Sounds
    Sound player_walk;
    Sound player_jump;
    Sound enemy_sound;

    // Constructor & Destructor
    assets_manager();
    ~assets_manager();
};


