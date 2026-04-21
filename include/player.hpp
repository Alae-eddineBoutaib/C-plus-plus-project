
#pragma once
#include <raylib.h>
#include <iostream>


enum state {idle , running, jumping};
struct player
{
    //player properties
    Texture2D sprite_idle;
    Texture2D sprite_run;
    Texture2D sprite_jump;
    Sound jump_sound;
    Sound walking_sound;
    float scale;
    float width;
    Vector2 position;
    float height;
    int lives;
    Rectangle frame_rec;
    int current_frame;
    int frames_counter;
    int frames_speed;
    int max_frames;
    int run_max_frames;
    enum state game_state;
    int direction;
    bool on_ground;
    bool on_ladder;
    bool is_hurt;
    int hurt_timer;

    //movements
    float horizontal_movement;
    float yspeed;
    float gravity;
    
    //methods
    player(float start_x, float start_y, Texture2D mc_sprite_idle, Texture2D mc_sprite_jump, Texture2D mc_sprite_run, Sound jump_sound);
    ~player();
    void update_animation();
    void update(float groundy);
    void Draw();

};

