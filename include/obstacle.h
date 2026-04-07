#include <iostream>
#include <raylib.h>
#include <cmath>

using namespace std;

enum type_of_obstacle{
    tall_obstacle,
    small_obstacle,
    wide_obstacle
};

struct obstacle{
    //obstacle properties
    Texture2D enemy;
    Sound enemy_sound;
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
    float patrol_distance;

    obstacle(float x, float y, type_of_obstacle type, bool moving);

    //methods
    ~obstacle();
    void update();
    void Draw();

};


