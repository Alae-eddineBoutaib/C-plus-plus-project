#pragma once
#include <iostream>
#include <raylib.h>
#include <cmath>

using namespace std;

enum type_of_obstacle {spike ,moving_pad, box, tree_monster, man, minion};


struct obstacle{
    //obstacle properties
    Texture2D enemy_1;
    Texture2D enemy_2;
    Texture2D enemy_3;
    Texture2D the_box;
    float scale;
    Vector2 position;
    float width;
    float height;
    type_of_obstacle the_type;
    Rectangle frame_rec;
    int current_frame;
    int frames_counter;
    int frames_speed;
    int max_frames;
    int run_max_frames;
    bool is_harmful;

    //obstacle movement
    bool is_moving;
    float speed;
    int direction;
    float start_x;
    float start_y;
    float patrol_distance;
    
    obstacle(float x, float y, bool moving, type_of_obstacle type, Texture2D boxe, Texture2D tex1, Texture2D tex2, Texture2D tex3);

    //methods
    ~obstacle();
    void update_animation();
    void update();
    void Draw();

};