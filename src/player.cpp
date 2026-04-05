#include "../include/player.h"


//Constructor logic
player::player(float start_x, float start_y){
    position_x = start_x;
    position_y = start_y;
    width = 50;
    height = 50;
    lives = 3;
    
    yspeed = 0;
    gravity = 1;
    horizontal_movement = 5;
}

//Movement logic
void player::update(float groundy){
    if(IsKeyDown(KEY_D)) position_x += horizontal_movement;
    if(IsKeyDown(KEY_A)) position_x -= horizontal_movement;
    if(IsKeyPressed(KEY_SPACE) && position_y >= groundy) {
            yspeed = -20;
    }
    yspeed += gravity;
    position_y += yspeed;
    

    if(position_y > groundy){
        position_y = groundy;
        yspeed = 0;
    }

}

//Drawing logic
void player::Draw(){
    DrawRectangle((int) position_x, (int) position_y,(int) width,(int) height, WHITE);

}