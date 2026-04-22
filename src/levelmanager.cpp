#include "../include/levelmanager.hpp"

levelmanager::levelmanager(assets_manager& vault, float groundy){
    current_level = 0;

    // LEVEL 1 - gentle, no spikes, wide platforms, 2 moving pads
    level* level1 = new level;
    levels.push_back(level1);
    const char* level1_map[] = {
        "..................................................................................................C..............G",
        "..................................................................................................T..............T",
        ".....C....................C.........................................C.............................T..............TTTTTT",
        ".....TTTTTTT..........TTTTTTT..............................TTTTTTTTT.......................TTTTTTT..............TTTTTT",
        "TTTTTTTTTTTT..........TTTTTTT....MMMMMM.............MMMMMMTTTTTTTTT.....MMMMMM.........TTTTTTT................TTTTTT",
        "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT.",
    };
    level1->load_from_grid(level1_map, 6, 80, 32, vault, groundy);

    // LEVEL 2 - introduces spikes, wide buffers
    level* level2 = new level;
    levels.push_back(level2);
    const char* level2_map[] = {
        "......................................................................................................C..............G",
        "......................................................................................................T.............TT",
        ".....C....................C..................C..............................C.............................T........TTTTTT",
        ".....TTTTTTT..........TTTTTTT........TTTTTTTTT.......MM...........TTTTTTTTT.......................TTTTTTT.........TTTTTT",
        "TTTTTTTTTTTT..........TTTTTTT........TTTTTTTTT....S.....S..........TTTTTTTTT.....MMMMMM.........TTTTTTT.........TTTTTT",
        "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT.",
    };
    level2->load_from_grid(level2_map, 6, 80, 32, vault, groundy);

    // LEVEL 3 - more spikes, same gap rules
    level* level3 = new level;
    levels.push_back(level3);
    const char* level3_map[] = {
        "..........................................................................................................C..............G",
        "..........................................................................................................T.............TT",
        "........C.................C..................C......................................C................................TTTTT........TTTTTT",
        ".....TTTTTTT..........TTTTTTT........TTTTTTTTT......MM..............TTTTTTTTT.....TTTTTTT.....MM...................TTTTTTTTT............TTTTTT",
        "TTTTTTTTTTTT..........TTTTTTT........TTTTTTTTT....S.....S...............TTTTTTTTT...TTTTTTT.S.....S...........TTTTTTTTT................TTTTTT",
        "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT.",
    };
    level3->load_from_grid(level3_map, 6, 80, 32, vault, groundy);

    // LEVEL 4 - introduces ladders, upper floor reachable
    level* level4 = new level;
    levels.push_back(level4);
    const char* level4_map[] = {
        ".....C.......................C................................C...............................C....................G",
        ".......TTTTTTT.......MM........TTTTTTT.....MM....MM....MM.....TTTTTTT.....MM.........MM......TTTTTTT.........TTTTTT",
        ".....LL......................LL............S...........S....LL.............................LL..............LL",
        ".....LL......................LL.............................LL.............................LL..............LL",
        ".....LL......................LL..........MM.................LL.............................LL..............LL",
        "TTTTTTTTTTT..........TTTTTTTTTT........S.....S...........TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT.......TTTTTTTTTTTTT.",
        "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT.",
    };
    level4->load_from_grid(level4_map, 7, 80, 32, vault, groundy);

    // LEVEL 5 - ladders + spikes combination
    level* level5 = new level;
    levels.push_back(level5);
    const char* level5_map[] = {
        ".....C.......................C................................C.............................C....................G",
        ".......TTTTTTT....MM......MM...TTTTTTT......MM.........MM.....TTTTTTT........................TTTTTTT..MM....TTTTTT",
        ".....LL......................LL.............................LL.............................LL..........S...LL",
        ".....LL......................LL.............................LL.............................LL..............LL",
        ".....LL......................LL......MM.....................LL.............................LL..............LL",
        "TTTTTTTTTTT..........TTTTTTTTTT....S.....S...............TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT.........TTTTTTTTTTTTT.",
        "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT.",
    };
    level5->load_from_grid(level5_map, 7, 80, 32, vault, groundy);

    // LEVEL 6 - harder spikes, longer gaps
    level* level6 = new level;
    levels.push_back(level6);
    const char* level6_map[] = {
        ".....C.......................C................................C.............................C....................G",
        ".......TTTTTTT.................TTTTTTT.....MM......MM......TTTTTTT......MM...........MM......TTTTTTT.........TTTTTT",
        ".....LL......................LL................SS........LL................................LL..............LL",
        ".....LL......................LL..........................LL................................LL..............LL",
        ".....LL......................LL..........................LL................................LL..............LL",
        "TTTTTTTTTTT.......TTTTTTTTTTTTT........................TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT...............TTTTTTTTTTTTT.",
        "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT.",
    };
    level6->load_from_grid(level6_map, 7, 80, 32, vault, groundy);

    // LEVEL 7 - tight gaps, multiple ladders
    level* level7 = new level;
    levels.push_back(level7);
    const char* level7_map[] = {
        ".....C.................C.......................C................................C................................C..G",
        ".......TTTTTTT.....MM....TTTTTTT.......MM........TTTTTTT......MM.......MM.......TTTTTTT........................TTTTTTTTTTTTT",
        ".....LL................LL......................LL.............................LL.............................LL.......LL",
        ".....LL................LL.............SSS......LL.............................LL.............................LL.......LL",
        ".....LL................LL......................LL.............................LL.............................LL.......LL",
        "TTTTTTTTTTT....TTTTTTTTTT.....................TTTTTTTT......S.......S......TTTTTTTTTTTTTTTTTTTTTTTTTTTTTT.......TTTTTTTTTTTTT.",
        "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT.",
    };
    level7->load_from_grid(level7_map, 7, 80, 32, vault, groundy);

    // LEVEL 8 - very hard, lots of spikes
    level* level8 = new level;
    levels.push_back(level8);
    const char* level8_map[] = {
        ".....C.................C.......................C................................C.................................C..G",
        ".......TTTTTTT...........TTTTTTT....MM.....MM....TTTTTTT.....MM.......MM........TTTTTTT....MM.....MM....MM.....TTTTTTTTTTTTT",
        ".....LL................LL......................LL.............................LL..........SSS.......SSS......LL.......LL",
        ".....LL................LL......................LL.............................LL.............................LL.......LL",
        ".....LL................LL......................LL.............................LL.............................LL.......LL",
        "TTTTTTTTTTT....TTTTTTTT.....SS.......SS.......TTTTTTTT.....SS.......SS.......TTTTTTTTTTTTTTTTTTTTTTTTTTTTTT.......TTTTTTTTTTTTT.",
        "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT.",
    };
    level8->load_from_grid(level8_map, 7, 80, 32, vault, groundy);

    // LEVEL 9 - brutal final level
    level* level9 = new level;
    levels.push_back(level9);
    const char* level9_map[] = {
        "..........C.................C.......................C..........................C..................................C...G",
        ".......TTTTTTT....MM.....TTTTTTT.......MM........TTTTTTT......MM......MM........TTTTTTT......MM.......MM.......TTTTTTTTTTTTT",
        ".....LL................LL..........SSS...SSS...LL.............................LL............SSS.......SSS....LL.......LL",
        ".....LL................LL......................LL.............SSS.....SSS.....LL.............................LL.......LL",
        ".....LL................LL......................LL.............................LL.............................LL.......LL",
        "TTTTTTTTTTT....TTTTTTTTTT............SSS......TTTTTTTT.......................TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT....TTTTTTTTTTTTT.",
        "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT.",
    };
    level9->load_from_grid(level9_map, 7, 80, 32, vault, groundy);
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