#include "../include/player.h"


//Constructor logic
player::player(float start_x, float start_y, Texture2D mc_sprite_idle, Texture2D mc_sprite_run, Texture2D mc_sprite_jump,Sound jump_sound){
    scale = 0.5f;
    position.x = start_x;
    position.y = start_y;
    sprite_idle = mc_sprite_idle;
    sprite_run = mc_sprite_run;
    sprite_jump = mc_sprite_jump;
    max_frames = 8;
    frames_speed = 3;
    frames_counter = 0;
    current_frame = 0;
    frame_rec.width = (float) sprite_idle.width / max_frames;
    frame_rec.height = (float) sprite_idle.height;
    frame_rec.x = 0;
    frame_rec.y = 0;

    width = sprite_idle.width / max_frames;
    height = sprite_idle.height;

    lives = 3;    
    yspeed = 0;
    gravity = 1;
    horizontal_movement = 5;
}

//Destructor logic
player::~player() {

}

//animation logic
void player::update_animation(){
        frames_counter++;
        if(frames_counter >= frames_speed) {
            frames_counter = 0;
            current_frame++;
            if(current_frame >= max_frames){
                current_frame = 0;
            }    
        }
        frame_rec.x = (float) current_frame * frame_rec.width;
}

//Movement logic
void player::update(float groundy){
    game_state = idle;
    if(IsKeyDown(KEY_D)){ 
        game_state = running;
        position.x += horizontal_movement;
    }
    if(IsKeyDown(KEY_A)) {
        game_state = running;
        position.x -= horizontal_movement;
    }
    if(IsKeyPressed(KEY_SPACE) && position.y >= groundy - height) {
        game_state = jumping;
        yspeed = -25;
    }
    yspeed += gravity;
    position.y += yspeed;
    update_animation();

    if(position.y > groundy - height){
        position.y = groundy - height;
        yspeed = 0;
    }
}

//Drawing logic
void player::Draw(){
    if(game_state == idle){
        DrawTextureRec(sprite_idle, frame_rec, position, WHITE);
    }else if(game_state == running){
        DrawTextureRec(sprite_run, frame_rec, position, WHITE);
    }else if(game_state == jumping){
        DrawTextureRec(sprite_jump, frame_rec, position, WHITE);
    }
}