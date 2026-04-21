#include "../include/assets.hpp"

assets_manager::assets_manager() {
    player_sprite_idle = LoadTexture("assets/images/Swordsman/Idle.png");
    player_sprite_run = LoadTexture("assets/images/Swordsman/Run.png");
    player_sprite_jump = LoadTexture("assets/images/Swordsman/Jump.png");
    spike = LoadTexture("assets/images/objects/spikes.png");
    grass = LoadTexture("assets/images/tileset/Tile_01.png");
    box = LoadTexture("assets/images/objects/box.png");
    ladder = LoadTexture("assets/images/objects/Ladder1.png");
    player_jump = LoadSound("assets/sounds/jump.mp3");
    coin_pickup = LoadSound("assets/sounds/coin pick up.mp3");
    
}

assets_manager::~assets_manager() {
    UnloadTexture(player_sprite_idle);
    UnloadTexture(player_sprite_run);
    UnloadTexture(player_sprite_jump);
    UnloadTexture(spike);
    UnloadTexture(grass);
    UnloadTexture(ladder);
    UnloadTexture(box);
    UnloadSound(player_jump);
    UnloadSound(coin_pickup);
}
