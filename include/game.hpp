#pragma once

#include "player.hpp"
#include "obstacle.hpp"
#include "assets.hpp"
#include "coin.hpp"
#include "UI.hpp"

struct levelmanager;

enum ScreenState { MENU, STAGES, KEYBINDS, GAMEPLAY };

struct Game {
    int screen_width;
    int screen_height;

    bool gameover;
    int collected_coins;

    int selected_menu_option;
    int selected_stage_option;
    bool should_exit;

    float groundy;
    ScreenState current_screen;

    Camera2D camera;
    assets_manager vault;
    UI* game_ui;

    player* my_player;

    levelmanager* lvl_manager;

    Game(int width, int height);
    ~Game();

    void update();
    void draw();
    void reset();
};