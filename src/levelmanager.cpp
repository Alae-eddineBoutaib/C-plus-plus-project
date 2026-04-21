#include "../include/levelmanager.hpp"

levelmanager::levelmanager(assets_manager& vault,float groundy){
    current_level = 0;

    // ==================================================
    // LEVEL 1 SETUP
    // ==================================================
    level* level1 = new level;
    levels.push_back(level1);
    //LEVEL MAP
    const char* level1_map[] = {
        "................................................................................................G",
        "................................................................................................T",
        "..............C.......C..............................................C.........................TT",
        "....TTTT......TTTT....TTTT....................TTTT.........TTTT.......TTTT..................TTTT..",
        "TTTTT....MM..........M.....TTTTTTT...MM...TTTTTTT...MM....TTTTT..MM...TTTTTT................TT.",
        "TTTTT..............................................TTTTTTTTTTTTT.......TTTTTTTTTTTTTTTTTTTTTTTT.",
    };

    level1->load_from_grid(level1_map, 6, 80, 32, vault, groundy);
    // ==================================================
    // LEVEL 2 SETUP
    // ==================================================
    level* level2 = new level;
    levels.push_back(level2);
    //LEVEL MAP
    const char* level2_map[] = {
        ".....................................................................................................G",
        ".....................................................................................................T",
        "...............C.........C.......................................C.............................C....TT",
        "....TTTT.......TTTT......TTTT...............TTTT.............TTTT.....TTTT.....................TTTT..",
        "TTTTT..MM....S.....S....M.....TTTTTTT..MM..TTTTT..MM.......TTTTT...S...S...TTTTTTT..MM......TTTTT.",
        "TTTTT...............................................TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT.",
    };

    level2->load_from_grid(level2_map, 6, 80, 32, vault, groundy);
    // ==================================================
    // LEVEL 3 SETUP
    // ==================================================
    level* level3 = new level;
    levels.push_back(level3);
    //LEVEL MAP
    const char* level3_map[] = {
        "........................................................................................................G",
        "........................................................................................................T",
        ".............C......C.........C...................C.............C..............C....................C..TT",
        "...TTTT......TTT....TTT.......TTTT........TTTT...TTT...........TTT............TTT..................TTTT.",
        "TTTT...MM..S.....SS....S.MM..TTTTT.MM..TTTTTT...TTT..MM.....STTTS.MM.......STTTSS..MM.........TTTTT..",
        "TTTT..............................................TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT.",
    };

    level3->load_from_grid(level3_map, 6, 80, 32, vault, groundy);
    // ==================================================
    // LEVEL 4 SETUP
    // ==================================================
    level* level4 = new level;
    levels.push_back(level4);
    const char* level4_map[] = {
        "..............C..................................C.................................C....................G",
        "..............T..................................T.................................T....................T",
        "....TTTT......T....L.....TTTT.....L..............T....L....TTTT..............TTTT.L.................TT",
        "....TTTT......T....L....S...S.....L....TTTT.....TT....L....TTTT...TTTT.......TTTT.L..............TTTT.",
        "TTTTTTTTT.MM..T....L.TTTTTTTTT...L..TTTTTT...TTTT.MM.L..TTTTTTTTTTTTT.MM...TTTTT.L.MM..........TTTT.",
        "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT.",
    };

    level4->load_from_grid(level4_map, 6, 80, 32, vault, groundy);
    // ==================================================
    // LEVEL 5 SETUP
    // ==================================================
    level* level5 = new level;
    levels.push_back(level5);
    const char* level5_map[] = {
        "..C.....................................C.....................................C..............................G",
        "..T.....................................T.....................................T..............................T",
        "..T....L....TTTT......L.................T....L....TTT.........L...............T...L...TTTT.................TT",
        "..T....L....TTTT..S...L....TTTT.....S..T....L....TTT...TTTT..L....TTTT......T...L...TTTT...S.S..TTTT....TTTT",
        "TTTTT.MM.L..TTTT..S.MMLL.TTTTTT....STTTTT.MM.L..TTTTTTTTTT.MM.L.TTTTTT.MM.TT.ML...TTTTTSSTTTTTTTTTT..TTTT.",
        "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT.",
    };

    level5->load_from_grid(level5_map, 6, 80, 32, vault, groundy);
    // ==================================================
    // LEVEL 6 SETUP
    // ==================================================
    level* level6 = new level;
    levels.push_back(level6);
    const char* level6_map[] = {
        "C.......................................C.....................................C...................................G",
        "T.......................................T.....................................T...................................T",
        "T..L....TTTT......L....TTT..L...........T....L....TTT.........L....TTT......T...L....TTT........L....TTT......TT",
        "T..L....TTTT..S...L....TTT..L..TTTT.S..T....L....TTT...TTTT..L....TTT.S...T...L....TTT..S.S...L....TTTT....TTTT",
        "T.ML..STTTTTSS..MMLL.STTTTML.TTTTTTSSTTTT.MM.L.STTTTTTTTTTT.ML.STTTTTSS.TTTT.ML.STTTTTSSTTTTTTTTTT.ML...STTTT.",
        "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT.",
    };

    level6->load_from_grid(level6_map, 6, 80, 32, vault, groundy);
    // ==================================================
    // LEVEL 7 SETUP
    // ==================================================
    level* level7 = new level;
    levels.push_back(level7);
    const char* level7_map[] = {
        "C..............C.......................C............................C.............................C......................G",
        "T..............T.......................T............................T.............................T......................T",
        "T.L..TTTT.L....T...L...TTT.L..........T....L...TTT......L..........T....L....TTT......L.........T...L...TTTT.........TT",
        "T.L..TTTT.L.S..T...L...TTT.L..TTTT....T.S..L...TTT.TTTT.L.S.......T.S..L....TTT.TTTT.L.S......T...L...TTTT..S.S...TTTT",
        "T.ML.TTTTTLSSTTTTML.STTTTTML.TTTTTTSSTTTTTML.STTTTTTTTTTTML.SSTTTTTML.STTTTTTTTTTTTTML.SS.TTTTTTML.STTTTTTSSTTTTTTTTTT.",
        "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT.",
    };

    level7->load_from_grid(level7_map, 6, 80, 32, vault, groundy);
    // ==================================================
    // LEVEL 8 SETUP
    // ==================================================
    level* level8 = new level;
    levels.push_back(level8);
    const char* level8_map[] = {
        "C...C..............C.....C.......................C....C..........................C....C...........................C.....G",
        "T...T..............T.....T.......................T....T..........................T....T...........................T.....T",
        "T.L.T.L..TTTT.L....T..L..T...L...TTT.L..........TL...T....L...TTT......L......TL....T....L....TTT......L.......TL...TT",
        "T.L.T.L..TTTT.LS...T..L..T...L...TTT.L..TTTT....TL.S.T.S..L...TTT.TTTT.L.S...TL.S..T.S..L....TTT.TTTT.L.S....TL..TTTT",
        "TMLTTTML.TTTTTLSSTTTTMLTTML.STTTTTML.TTTTTTSSTTTTTMLSTTTTTML.STTTTTTTTTTTML.SSTTTTMTSTTTTTML.STTTTTTTTTTTML.SS.TTTTTTT.",
        "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT.",
    };

    level8->load_from_grid(level8_map, 6, 80, 32, vault, groundy);
    // ==================================================
    // LEVEL 9 SETUP
    // ==================================================
    level* level9 = new level;
    levels.push_back(level9);
    const char* level9_map[] = {
        "C.C...C..............C..C.....C.......................C...C..C..........................C..C...C.................C.....G",
        "T.T...T..............T..T.....T.......................T...T..T..........................T..T...T.................T.....T",
        "T.TL..TL.TTTT.L......T.TL.....T...L...TTT.L..........TL..TL..T....L...TTT......L......TL.TL..T....L....TTT....TL....TT",
        "T.TL..TL.TTTT.LS.S...T.TL..S..T.S.L...TTT.L..TTTT...TL.STL.ST.S..L...TTT.TTTT.L.SS..TL.TLS.T.SS.L....TTT....TL..STTTT",
        "TTMLSSTML.TTTTTLSSTTTTTML.SSTTTTML.STTTTTML.TTTTTTSSTTTTML.TTTML.STTTTTTTTTTTML.SSTTTTML.TTMLSSTTTTTML.STTTTTTTML.STTTT.",
        "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT.",
    };

    level9->load_from_grid(level9_map, 6, 80, 32, vault, groundy);
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