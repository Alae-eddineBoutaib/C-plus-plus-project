#include "../include/obstacle.h"  

//Constructor logic
obstacle::obstacle(float x, float y, type_of_obstacle type, bool moving){
    position_x = x;
    position_y = y;
    the_type = type;
    is_moving = moving;

    direction = -1;
    start_x = position_x;
    patrol_distance = 60;
    speed = 3.0f;

    switch (the_type) {
        case type_of_obstacle::tall_obstacle:
            width = 40.0f;
            height = 100.0f;
            break;
        case type_of_obstacle::small_obstacle:
            width = 20.0f;
            height = 20.0f;
            break;
        case type_of_obstacle::wide_obstacle:
            width = 120.0f;
            height = 40.0f;
            break;        
        }
}

//Movement logic
void obstacle::update(){
    if(is_moving == true) {
        position_x = position_x + (speed * direction);
    }
    float distance_traveled = start_x - position_x;
    if(abs((int) distance_traveled) >= patrol_distance){
        direction = direction * (-1);
    }
}

//Drawing logic
void obstacle::Draw(){
    switch (the_type)
    {
    case type_of_obstacle::small_obstacle:
        DrawRectangle((int) position_x,(int) position_y,(int) width,(int) height, RED);
        break;
    case type_of_obstacle::tall_obstacle:
        DrawRectangle((int) position_x,(int) position_y,(int) width,(int) height, BLUE);
        break;
    case type_of_obstacle::wide_obstacle:
        DrawRectangle((int) position_x,(int) position_y,(int) width,(int) height, GREEN);
        break;
    }
}