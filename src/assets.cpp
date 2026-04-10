#pragma once
#include "../include/assets.h"


assets_manager::assets_manager() {

    ghost_sprite = LoadTexture("assets/images/retro enemy 2.png");
    skeleton_sprite = LoadTexture("assets/images/retro enemy 4.png");
    robot_sprite = LoadTexture("assets/images/retro enemy 6.png");
    
}

assets_manager::~assets_manager() {

    UnloadTexture(player_sprite);
    UnloadTexture(ghost_sprite);
    UnloadTexture(skeleton_sprite);
    UnloadTexture(robot_sprite);
    
}