#include "../include/obstacle.hpp"  

//Constructor logic
obstacle::obstacle(float x, float y, bool moving, type_of_obstacle type, Texture2D boxe , Texture2D spikes){
    box_scale = 1.0f;
    position.x = x;
    is_moving = moving;

    spike_texture = spikes;
    the_box = boxe;
    frame_rec.x = 0;
    frame_rec.y = 0;
    is_harmful = true;

    the_type = type;

    switch (the_type)
    {
        case spike:
            is_harmful = true;
            is_moving = false;
            frame_rec.width = spike_texture.width;
            frame_rec.height = spike_texture.height;
            break;
        case moving_pad:
            is_harmful = false;
            is_moving = true;
            frame_rec.width = 100;
            frame_rec.height = 20;
            break;
        case box:
            is_harmful = false;
            is_moving = false;

            frame_rec.width = the_box.width;
            frame_rec.height = the_box.height;
            width = frame_rec.width * box_scale;
            height = frame_rec.height * box_scale;
            break;
    }

    if(the_type != box){
        width = frame_rec.width;
        height = frame_rec.height;
    }
    position.y = y - height;

    direction = -1;
    start_x = position.x;
    start_y = position.y;
    patrol_distance = 150;
    speed = 3.0f;
}

//Destructor logic
obstacle::~obstacle(){
}

//Movement logic
void obstacle::update(){
    float distance_traveled;
    switch (the_type)
    {
        case spike:
            break;
        case moving_pad:
            position.x = position.x + (speed * direction);
            distance_traveled = start_x - position.x;
            if(abs(distance_traveled) >= patrol_distance){
                    direction = direction * (-1);
            }
            break;
        case box:
            break;
        }
}

//Drawing logic
void obstacle::Draw(){
    switch (the_type) {
        case box:
            DrawTextureEx(the_box, position, 0.0f, box_scale, WHITE);
            break;

        case moving_pad:
            //DrawTextureEx(the_box, position, 0.0f, box_scale, WHITE);
            DrawRectangle(position.x, position.y, width, height, DARKPURPLE);
            break;
        case spike:
            DrawTextureEx(spike_texture, position, 0.0f, box_scale, WHITE);
            break;
    }
}