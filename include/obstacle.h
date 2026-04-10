#include <iostream>
#include <raylib.h>
#include <cmath>

using namespace std;

enum type_of_obstacle { ghost_obstacle, skeleton_obstacle, robot_obstacle};


struct obstacle{
    //obstacle properties
    Texture2D enemy_1;
    Texture2D enemy_2;
    Texture2D enemy_3;
    float scale;
    Vector2 position;
    float width;
    float height;
    type_of_obstacle the_type;

    //obstacle movement
    bool is_moving;
    float speed;
    int direction;
    float start_x;
    float start_y;
    float patrol_distance;
    
    obstacle(float x, float y, bool moving, Texture2D tex1, Texture2D tex2, Texture2D tex3);

    //methods
    ~obstacle();
    void update();
    void Draw();

};


