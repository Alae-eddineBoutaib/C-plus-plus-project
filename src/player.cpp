#include "../include/player.h"


//Constructor logic
player::player(float start_x, float start_y){
    scale = 0.5f;
    sprite = LoadTexture("assets/images/retro mc.png");
    jump_sound = LoadSound("assets/sounds/jump.mp3");
    walking_sound = LoadSound("assets/sounds/footsteps.mp3");
    position_x = start_x;
    position_y = start_y;
    width = sprite.width * scale;
    height = sprite.height * scale;
    lives = 3;
    
    yspeed = 0;
    gravity = 1;
    horizontal_movement = 5;
}

//Movement logic
void player::update(float groundy){
    if(IsKeyDown(KEY_D)){ 
        position_x += horizontal_movement;
        PlaySound(walking_sound);
    }
    if(IsKeyDown(KEY_A)) {
        position_x -= horizontal_movement;
        PlaySound(walking_sound);
    }
    if(IsKeyPressed(KEY_SPACE) && position_y >= groundy - height) {
            yspeed = -30;
            PlaySound(jump_sound);
    }
    yspeed += gravity;
    position_y += yspeed;
    

    if(position_y > groundy - height){
        position_y = groundy - height;
        yspeed = 0;
    }
    if(!IsSoundPlaying(walking_sound)){
        PlaySound(walking_sound);
    }

}

//Drawing logic
void player::Draw(){
    Vector2 position = {position_x, position_y};
    DrawTextureEx(sprite, position, 0.0f, scale, WHITE);
}