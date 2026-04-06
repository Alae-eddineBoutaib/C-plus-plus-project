#include "../include/obstacle.h"  

//Constructor logic
obstacle::obstacle(float x, float y, type_of_obstacle type, bool moving){
    scale = 0.5f;
    enemy = LoadTexture("assets/images/retro enemy 2.png");
    enemy_sound = LoadSound("assets/sounds/monster sound 2.mp3");
    position_x = x;
    position_y = y;
    the_type = type;
    is_moving = moving;
    width = enemy.width * scale;
    height = enemy.height * scale;

    direction = -1;
    start_x = position_x;
    patrol_distance = 60;
    speed = 3.0f;

}

//Movement logic
void obstacle::update(){
    if(is_moving == true) {
        position_x = position_x + (speed * direction);
        PlaySound(enemy_sound);
    }
    float distance_traveled = start_x - position_x;
    if(abs((int) distance_traveled) >= patrol_distance){
        direction = direction * (-1);
    }
    if(!IsSoundPlaying(enemy_sound)){
        PlaySound(enemy_sound);
    }
}

//Drawing logic
void obstacle::Draw(){
    Vector2 position = {position_x, position_y};
    DrawTextureEx(enemy, position, 0.0f, scale, WHITE);
}