#pragma once
#include <vector>
#include "../include/obstacle.hpp"
#include "../include/coin.hpp"

using namespace std;

struct level {
    vector<obstacle*> obstacles;
    vector<coin*> coins;

    level();
    ~level();

    void update();
    void draw();
    void reset(); 
};