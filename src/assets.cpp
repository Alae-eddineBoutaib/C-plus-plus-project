#include "../include/assets.hpp"

assets_manager::assets_manager() {
    player_sprite_idle = LoadTexture("assets/images/Swordsman/Idle.png");
    player_sprite_run = LoadTexture("assets/images/Swordsman/Run.png");
    player_sprite_jump = LoadTexture("assets/images/Swordsman/Jump.png");
    spike = LoadTexture("assets/images/objects/spikes.png");
    grass = LoadTexture("assets/images/tileset/Tile_01.png");
    box = LoadTexture("assets/images/objects/box.png");
    ladder = LoadTexture("assets/images/objects/Ladder1.png");
    player_jump = LoadSound("assets/sounds/jump.mp3");
    coin_pickup = LoadSound("assets/sounds/coin pick up.mp3");
    menu_switch = LoadSound("assets/sounds/button menu switch.mp3");
    SetSoundVolume(menu_switch, 0.55f);
    ui_music = LoadMusicStream("assets/sounds/Intro Pixel Art 8 bit--Laugh.mp3");
    SetMusicVolume(ui_music, 0.35f);
    gameplay_music_1 = LoadMusicStream("assets/sounds/Kubbi - Digestive biscuit  NO COPYRIGHT 8-bit Music.mp3");
    gameplay_music_2 = LoadMusicStream("assets/sounds/Joshua McLean - Mountain Trials  NO COPYRIGHT 8-bit Music.mp3");
    gameplay_music_3 = LoadMusicStream("assets/sounds/Eric Skiff - A Night Of Dizzy Spells  NO COPYRIGHT 8-bit Music  Background.mp3");
    gameplay_music_4 = LoadMusicStream("assets/sounds/8-bit RPG Music  Boss Battle.mp3");
    SetMusicVolume(gameplay_music_1, 0.40f);
    SetMusicVolume(gameplay_music_2, 0.40f);
    SetMusicVolume(gameplay_music_3, 0.40f);
    SetMusicVolume(gameplay_music_4, 0.40f);
    goal = LoadTexture("assets/images/objects/goal.png");
    background1 = LoadTexture("assets/images/backgound1/1.png");
    background2 = LoadTexture("assets/images/background2/1.png");
}

assets_manager::~assets_manager() {
    UnloadTexture(player_sprite_idle);
    UnloadTexture(player_sprite_run);
    UnloadTexture(player_sprite_jump);
    UnloadTexture(spike);
    UnloadTexture(grass);
    UnloadTexture(ladder);
    UnloadTexture(goal);
    UnloadTexture(box);
    UnloadTexture(background1);
    UnloadTexture(background2);
    UnloadSound(player_jump);
    UnloadSound(coin_pickup);
    UnloadSound(menu_switch);
    UnloadMusicStream(ui_music);
    UnloadMusicStream(gameplay_music_1);
    UnloadMusicStream(gameplay_music_2);
    UnloadMusicStream(gameplay_music_3);
    UnloadMusicStream(gameplay_music_4);
}
