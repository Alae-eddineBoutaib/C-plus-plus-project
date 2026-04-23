#pragma once

#include <string>
#include "player.hpp"
#include "obstacle.hpp"
#include "assets.hpp"
#include "coin.hpp"
#include "UI.hpp"

struct levelmanager;

enum ScreenState { MENU, STAGES, KEYBINDS, GAMEPLAY, LEVEL_CLEAR, CHAPTER_CLEAR, GAME_COMPLETE };

struct Game {
    int screen_width;
    int screen_height;

    bool gameover;
    int collected_coins;

    int selected_menu_option;
    int selected_chapter_option;
    int selected_level_option;
    int selected_transition_option;
    int current_gameplay_track;
    bool should_exit;

    float groundy;
    ScreenState current_screen;

    Camera2D camera;
    assets_manager vault;
    UI* game_ui;
    std::string pending_transition_title;
    std::string pending_transition_subtitle;
    std::string pending_transition_story_title;
    std::string pending_transition_story;

    player* my_player;

    levelmanager* lvl_manager;

    Game(int width, int height);
    ~Game();

    void update();
    void draw();
    void reset();
    void prepare_level_transition();
    void advance_to_next_level();
    void handle_transition_input();
    void play_random_gameplay_music();
    void stop_gameplay_music();
};
