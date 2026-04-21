#pragma once
#include <iostream>
#include <raylib.h>
#include <cmath>

using namespace std;

enum type_of_obstacle {spike ,moving_pad, box};


class obstacle{
public: 
    //obstacle properties
    Texture2D the_box;
    Texture2D spike_texture;
    float box_scale;
    Vector2 position;
    float width;
    float height;
    type_of_obstacle the_type;
    Rectangle frame_rec;
    int current_frame;
    bool is_harmful;

    //obstacle movement
    bool is_moving;
    float speed;
    int direction;
    float start_x;
    float start_y;
    float patrol_distance;
    
    obstacle(float x, float y, bool moving, type_of_obstacle type, Texture2D boxe, Texture2D spikes);

    //methods
    ~obstacle();
    void update_animation();
    void update();
    void Draw();

};