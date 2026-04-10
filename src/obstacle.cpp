#include "../include/obstacle.h"  

//Constructor logic
obstacle::obstacle(float x, float y, bool moving, Texture2D enemy1, Texture2D enemy2, Texture2D enemy3){
    scale = 0.5f;
    position.x = x;
    position.y = y;
    is_moving = moving;
    enemy_1 = enemy1;
    enemy_2 = enemy2;
    enemy_3 = enemy3;

    int random_type = GetRandomValue(0, 2);
    the_type = (type_of_obstacle) random_type;

    switch (the_type)
    {
    case ghost_obstacle:
        width = enemy_1.width * scale;
        height = enemy_1.height * scale;
        break;
    case skeleton_obstacle:
        width = enemy_2.width * scale;
        height = enemy_2.height * scale;
        break;
    case robot_obstacle:
        width = enemy_3.width * scale;
        height = enemy_3.height * scale;
        break;
    }

    direction = -1;
    start_x = position.x;
    start_y = position.y;
    patrol_distance = 60;
    speed = 3.0f;

}

//Destructor logic
obstacle::~obstacle(){
    UnloadTexture(enemy_1);
    UnloadTexture(enemy_2);
    UnloadTexture(enemy_3);
}

//Movement logic
void obstacle::update(){
    float distance_traveled;
    switch (the_type)
    {
        case ghost_obstacle:
        {
            if(is_moving == true) {
                position.y = position.y + (speed * direction);
            }
            if(position.y <= start_y - patrol_distance){
                direction = 1;
            }
            else if(position.y >= start_y + patrol_distance){
                direction = -1;
            }
            break;
        }
        case skeleton_obstacle:
        case robot_obstacle:
            {
                if(is_moving == true) {
                    position.x = position.x + (speed * direction);
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
    switch (the_type)
    {
    case ghost_obstacle:
        DrawTextureEx(enemy_1, position, 0.0f, scale, WHITE);
        break;
    case skeleton_obstacle:
        DrawTextureEx(enemy_2, position, 0.0f, scale, WHITE);
        break;
    case robot_obstacle:
        DrawTextureEx(enemy_3, position, 0.0f, scale, WHITE);
        break;
    }
}