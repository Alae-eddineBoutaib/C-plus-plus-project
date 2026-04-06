#include <raylib.h>
#include <iostream>

struct player
{
    //player properties
    Texture2D sprite;
    Sound jump_sound;
    Sound walking_sound;
    float scale;
    float position_x;
    float position_y;
    float width;
    float height;
    int lives;

    //movements
    float horizontal_movement;
    float yspeed;
    float gravity;
    
    //methods
    player(float start_x, float start_y);
    void update(float groundy);
    void Draw();

};

