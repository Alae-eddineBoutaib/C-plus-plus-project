#include "../include/player.hpp"

player::player(float start_x, float start_y, Texture2D mc_sprite_idle, Texture2D mc_sprite_run, Texture2D mc_sprite_jump, Sound jump_sound){
    scale = 1.0f;
    position = {start_x, start_y};
    is_hurt = false;
    hurt_timer = 0;

    sprite_idle = mc_sprite_idle;
    sprite_run = mc_sprite_run;
    sprite_jump = mc_sprite_jump;

    max_frames = 8;
    frames_speed = 3;
    frames_counter = 0;
    current_frame = 0;

    frame_rec.width = (float)sprite_idle.width / max_frames;
    frame_rec.height = sprite_idle.height;
    frame_rec.x = 0;
    frame_rec.y = 0;

    direction = 1;

    width = frame_rec.width * scale;
    height = frame_rec.height * scale;

    lives = 3;

    yspeed = 0;
    gravity = 1.5;
    horizontal_movement = 5;

    on_ground = false;
}

player::~player() {}

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

void player::update(float groundy){
    if(IsKeyPressed(KEY_SPACE) && on_ground){
        yspeed = -18;
        on_ground = false;
    }

    on_ground = false;

    if(on_ladder){
        yspeed = 0;
        if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) position.y -= 3.0f;
        if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) position.y += 3.0f;
    } else {
        yspeed += gravity;
        position.y += yspeed;
    }

    if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)){ 
        position.x += horizontal_movement;
        direction = 1;
    }
    if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        position.x -= horizontal_movement;
        direction = -1;
    }
}

void player::Draw(){
    int prev_state = game_state;

    if(!on_ground){
        game_state = jumping;
    }
    else if(IsKeyDown(KEY_A) || IsKeyDown(KEY_D)){
        game_state = running;
    }
    else{
        game_state = idle;
    }
    
    Texture2D active_texture;
    int active_max_frames = 8; 

    if (game_state == idle) {
        active_texture = sprite_idle;
        active_max_frames = 8; 
    } 
    else if (game_state == running) {
        active_texture = sprite_run;
        active_max_frames = 8; 
    } 
    else {
        active_texture = sprite_jump;
        active_max_frames = 8; 
    }

    if (game_state != prev_state) {
        current_frame = 0;
        frames_counter = 0;
    }

    max_frames = active_max_frames; 

    frame_rec.width = (float)active_texture.width / max_frames;
    frame_rec.height = (float)active_texture.height;

    update_animation();

    Rectangle source = frame_rec;

    if(direction == -1){
        source.width = -frame_rec.width;
    }

    float art_width = frame_rec.width * scale;
    float art_height = frame_rec.height * scale;

    Rectangle dest = {
        position.x - (art_width - width) / 2.0f,
        position.y - (art_height - height),
        art_width,
        art_height
    };

    DrawTexturePro(active_texture, source, dest, {0, 0}, 0.0f, WHITE);
}