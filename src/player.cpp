#include "../include/player.h"


//Constructor logic
player::player(float start_x, float start_y, Texture2D mc_sprite_idle, Texture2D mc_sprite_run, Texture2D mc_sprite_jump,Sound jump_sound){
    scale = 1.0f;
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

    width = (sprite_idle.width / max_frames) * scale;
    height = sprite_idle.height * scale;

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
        yspeed = -20;
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
    Texture2D tex;
    if(game_state == idle){
        tex = sprite_idle;
    }else if(game_state == running){
        tex = sprite_run;
    }else if(game_state == jumping){
        tex = sprite_jump;
    }

    Rectangle dest = {
        position.x,
        position.y,
        frame_rec.width * scale,
        frame_rec.height * scale
    };

    DrawTexturePro(tex, frame_rec, dest, {0, 0}, 0.0f, WHITE);
}