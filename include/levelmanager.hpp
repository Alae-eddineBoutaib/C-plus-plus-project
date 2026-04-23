#pragma once
#include "raylib.h"
#include <vector>
#include "../include/level.hpp"
#include "../include/assets.hpp"

using namespace std;

struct levelmanager{
    vector<level*> levels;
    int current_level;

    levelmanager(assets_manager& vault, float groundy);
    ~levelmanager();

    void update();
    void draw();
    void reset_current_level();
    level* get_current_level();
};
