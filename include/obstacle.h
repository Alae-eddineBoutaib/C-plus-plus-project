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
    float position_x;
    float position_y;
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
    void update();
    void Draw();
};


