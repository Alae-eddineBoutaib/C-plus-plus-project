#include "../include/player.h"


//Constructor logic
player::player(float start_x, float start_y){
    scale = 0.5f;
    sprite = LoadTexture("assets/images/retro mc.png");
    jump_sound = LoadSound("assets/sounds/jump.mp3");
    walking_sound = LoadSound("assets/sounds/footsteps.mp3");

    position.x = start_x;
    position.y = start_y;

    width = sprite.width * scale;
    height = sprite.height * scale;

    lives = 3;    
    yspeed = 0;
    gravity = 1;
    horizontal_movement = 5;
}

//Destructor logic
player::~player() {
    UnloadTexture(sprite);
    UnloadSound(jump_sound);
    UnloadSound(walking_sound);
}

//Movement logic
void player::update(float groundy){
    if(IsKeyDown(KEY_D)){ 
        position.x += horizontal_movement;
        PlaySound(walking_sound);
        if(!IsSoundPlaying(walking_sound)){
            PlaySound(walking_sound);
        }
    }
    if(IsKeyDown(KEY_A)) {
        position.x -= horizontal_movement;
        PlaySound(walking_sound);
        if(!IsSoundPlaying(walking_sound)){
            PlaySound(walking_sound);
        }
    }
    if(IsKeyPressed(KEY_SPACE) && position.y >= groundy - height) {
            yspeed = -25;
            PlaySound(jump_sound);
    }
    yspeed += gravity;
    position.y += yspeed;
    

    if(position.y > groundy - height){
        position.y = groundy - height;
        yspeed = 0;
    }


}

//Drawing logic
void player::Draw(){
    DrawTextureEx(sprite, position, 0.0f, scale, WHITE);
}