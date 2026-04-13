#include "../include/obstacle.h"  

//Constructor logic
obstacle::obstacle(float x, float y, bool moving, Texture2D enemy1, Texture2D enemy2, Texture2D enemy3){
    scale = 1.0f;
    position.x = x;
    is_moving = moving;
    enemy_1 = enemy1;
    enemy_2 = enemy2;
    enemy_3 = enemy3;
    max_frames = 6;
    frames_speed = 3;
    frames_counter = 0;
    current_frame = 0;
    frame_rec.x = 0;
    frame_rec.y = 0;

    int random_type = GetRandomValue(0, 2);
    the_type = (type_of_obstacle) random_type;

    switch (the_type)
    {
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
    position.y = y - height + 10;

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
    switch (the_type)
    {
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

    Rectangle dest = {
        position.x,
        position.y,
        frame_rec.width * scale,
        frame_rec.height * scale
    };

    DrawTexturePro(Tex, frame_rec, dest, {0, 0}, 0.0f, WHITE);
}