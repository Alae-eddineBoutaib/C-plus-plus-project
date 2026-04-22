#pragma once
#include <vector>
#include "../include/obstacle.hpp"
#include "../include/coin.hpp"
#include "../include/assets.hpp"
#include <cstring>

using namespace std;

struct level {
    vector<obstacle*> obstacles;
    vector<coin*> coins;
    vector<Rectangle> ladders;
    Rectangle goal;
    Texture2D ladder_texture;
    Texture2D box_texture;
    Texture2D spike_texture;
    vector<Rectangle> terrain_tiles;
    Texture2D terrain_texture;
    Texture2D goal_texture;
    Sound coin_sound;
    float groundy;

    assets_manager vault;

    level();
    ~level();

    void load_from_grid(const char** map_data, int rows, int cols, float tile_size, assets_manager& vault, float ground_y);
    void update();
    void draw();
    void reset(); 
};