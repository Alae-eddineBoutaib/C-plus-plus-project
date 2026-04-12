#include "../include/assets.h"

assets_manager::assets_manager() {
    player_sprite_idle = LoadTexture("assets/images/Swordsman/Idle.png");
    player_sprite_run = LoadTexture("assets/images/Swordsman/Run.png");
    player_sprite_jump = LoadTexture("assets/images/Swordsman/Jump.png");
    enemy_1 =  LoadTexture("assets/images/enemy1/Walk.png");
    enemy_2 = LoadTexture("assets/images/enemy2/Walk.png");
    enemy_3 = LoadTexture("assets/images/enemy3/Walk.png");
    player_jump = LoadSound("assets/sounds/jump.mp3");
    coin_pickup = LoadSound("assets/sounds/coin pick up.mp3");
}

assets_manager::~assets_manager() {
    UnloadTexture(player_sprite_idle);
    UnloadTexture(player_sprite_run);
    UnloadTexture(player_sprite_jump);
    UnloadTexture(enemy_1);
    UnloadTexture(enemy_2);
    UnloadTexture(enemy_3);
    UnloadSound(player_jump);
    UnloadSound(coin_pickup);
}
