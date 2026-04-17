#include "../include/obstacle.hpp"  

//Constructor logic
obstacle::obstacle(float x, float y, bool moving, type_of_obstacle type, Texture2D boxe, Texture2D enemy1, Texture2D enemy2, Texture2D enemy3){
    scale = 2.0f;
    position.x = x;
    is_moving = moving;
    enemy_1 = enemy1;
    enemy_2 = enemy2;
    enemy_3 = enemy3;
    the_box = boxe;
    max_frames = 6;
    frames_speed = 3;
    frames_counter = 0;
    current_frame = 0;
    frame_rec.x = 0;
    frame_rec.y = 0;
    is_harmful = true;

    the_type = type;

    switch (the_type)
    {
        case spike:
            is_harmful = true;
            is_moving = false;
            frame_rec.width = 30;
            frame_rec.height = 30;
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

            frame_rec.x = 0;
            frame_rec.y = 0;
            frame_rec.width = the_box.width;
            frame_rec.height = the_box.height;
            break;
        case tree_monster:
            frame_rec.width = enemy_1.width / max_frames;
            frame_rec.height = enemy_1.height;
            break;
        case man:
            frame_rec.width = enemy_2.width / max_frames;
            frame_rec.height = enemy_2.height;
            break;
        case minion:
            frame_rec.width = enemy_3.width / max_frames;
            frame_rec.height = enemy_3.height;
            break;
    }

    width = frame_rec.width * scale;
    height = frame_rec.height * scale;
    position.y = y - height;

    direction = -1;
    start_x = position.x;
    start_y = position.y;
    patrol_distance = 60;
    speed = 3.0f;
}

//Destructor logic
obstacle::~obstacle(){
}

//animation logic
void obstacle::update_animation(){
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
        case tree_monster:
        case man:
        case minion:
            {
                if(is_moving == true) {
                    position.x = position.x + (speed * direction);
                    update_animation();
                }
                distance_traveled = start_x - position.x;
                if(abs(distance_traveled) >= patrol_distance){
                    direction = direction * (-1);
                }
                break;
            }

        }
}

//Drawing logic
void obstacle::Draw(){
    Texture2D Tex;
    bool has_texture = true;
    switch (the_type)
    {
        case spike:
            DrawTriangle(
                {position.x + (width / 2.0f), position.y}, 
                {position.x, position.y + height},         
                {position.x + width, position.y + height}, 
                GRAY
            );
            has_texture = false;
            break;
        case moving_pad:
            DrawRectangle(position.x, position.y, width, height, DARKPURPLE);
            has_texture = false;
            break;
        case box:
        {
            Rectangle source ={0, 0, (float) the_box.width,(float) the_box.height};
            Rectangle dest = {
                position.x,
                position.y,
                width,   
                height 
            };
            DrawTexturePro(the_box, source, dest, {0, 0}, 0.0f, WHITE);
            break;
        } 
        case tree_monster:
            Tex = enemy_1;
            break;
        case man:
            Tex = enemy_2;
            break;
        case minion:
            Tex = enemy_3;
            break;
    }

    if(has_texture){
        Rectangle dest = {
            position.x,
            position.y,
            frame_rec.width * scale,
            frame_rec.height * scale
    
        };
        DrawTexturePro(Tex, frame_rec, dest, {0, 0}, 0.0f, WHITE);
    }

}