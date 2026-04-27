#pragma once
#include <vector>
#include "../include/obstacle.hpp"
#include "../include/coin.hpp"
#include "../include/assets.hpp"
#include <cstring>

using namespace std;

enum BackdropTheme {
    BACKDROP_WOODS_SUN = 0,
    BACKDROP_WOODS_MOON = 1,
    BACKDROP_HAUNTED_GROVE = 2,
    BACKDROP_IRON_KEEP = 3,
    BACKDROP_CRYPT_CAVES = 4,
    BACKDROP_KNIGHT_WATCH = 5,
    BACKDROP_BLOOD_MOON = 6,
    BACKDROP_GHOST_HALL = 7,
    BACKDROP_FINAL_ECLIPSE = 8
};

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
    int backdrop_theme;
    assets_manager* vault;

    level();
    ~level();

    void load_from_grid(const char** map_data, int rows, int cols, float tile_size, assets_manager& vault, float ground_y);
    void update();
    void draw_background() const;
    void draw();
    void reset(); 
    void set_backdrop_theme(int theme);
};
