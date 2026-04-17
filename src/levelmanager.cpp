#include "../include/levelmanager.hpp"

levelmanager::levelmanager(assets_manager& vault,float groundy){
    current_level = 0;

    // ==================================================
    // LEVEL 1 SETUP
    // ==================================================
    level* level1 = new level;
    levels.push_back(level1);
    // Ground box (platform)
    level1->obstacles.push_back(
        new obstacle(400, groundy, false, box, vault.box, vault.enemy_1, vault.enemy_2, vault.enemy_3)
    );

    // Moving platform
    level1->obstacles.push_back(
        new obstacle(650, groundy - 150, true, moving_pad, vault.box, vault.enemy_1, vault.enemy_2, vault.enemy_3)
    );

    // Enemy
    level1->obstacles.push_back(
        new obstacle(900, groundy, true, tree_monster, vault.box, vault.enemy_1, vault.enemy_2, vault.enemy_3)
    );

    // Coins
    level1->coins.push_back(
        new coin(450, groundy - 80, 15.0f, 10, vault.coin_pickup)
    );

    level1->coins.push_back(
        new coin(700, groundy - 200, 15.0f, 10, vault.coin_pickup)
    );


    // ==================================================
    // LEVEL 2 SETUP
    // ==================================================
    level* level2 = new level;
    levels.push_back(level2);

    // ==================================================
    // LEVEL 3 SETUP
    // ==================================================
    level* level3 = new level;
    levels.push_back(level3);
}

//Destructor logic
levelmanager::~levelmanager(){
    for(auto lvl : levels) delete lvl;
}

//update logic
void levelmanager::update(){
    if(levels.size() > 0) levels[current_level]->update();
}

//draw logic
void levelmanager::draw(){
    if(levels.size() > 0) levels[current_level]->draw();
}

//reset the current level logic
void levelmanager::reset_current_level(){
    if(levels.size() > 0) levels[current_level]->reset();
}

//get current level logic
level* levelmanager::get_current_level(){
    return levels[current_level];
}