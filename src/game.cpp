#include "../include/game.hpp"
#include "../include/levelmanager.hpp"

namespace {
struct ChapterMeta {
    const char* title;
    const char* story;
};

const ChapterMeta GAME_CHAPTERS[3] = {
    {
        "Chapter I - Whispering Woods",
        "The journey begins beneath ancient trees where the hero follows a fading trail. Every jump through the forest reveals that something dark has started to wake beyond the roots."
    },
    {
        "Chapter II - Iron Ascent",
        "Past the forest waits a ruined stronghold of ladders, traps, and narrow ledges. The climb is no longer about discovery, but survival against a fortress that refuses to fall quietly."
    },
    {
        "Chapter III - Crown of Shadows",
        "At the summit, the path turns cruel and every mistake carries weight. The last chapter tests whether the hero can cross the shadowed crown and reach the gate before hope runs out."
    }
};
}

Game::Game(int width, int height) {
    screen_width = width;
    screen_height = height;
    should_exit = false;

    gameover = false;
    collected_coins = 0;

    selected_menu_option = 0;
    selected_chapter_option = 0;
    selected_level_option = 0;
    selected_transition_option = 0;
    current_gameplay_track = -1;

    groundy = screen_height - 100;
    current_screen = MENU;

    my_player = new player(64,groundy - 250, vault.player_sprite_idle,
                           vault.player_sprite_run,
                           vault.player_sprite_jump,
                           vault.player_jump);

    lvl_manager = new levelmanager(vault, groundy);
    game_ui = new UI(screen_width, screen_height);

    camera.target.x += (my_player->position.x - camera.target.x) * 0.1f;
    camera.target.y += (my_player->position.y - camera.target.y) * 0.1f;
    camera.offset = {(float)screen_width / 3, (float)screen_height * 0.7f};
    camera.zoom = 1.0f;
}

void Game::reset() {
    gameover = false;
    collected_coins = 0;
    my_player->yspeed = 0;
    my_player->on_ladder = false;
    my_player->hurt_timer = 0;
    my_player->is_hurt = false;
    my_player->lives = 3;
    my_player->position = {64, groundy - 250};  
    lvl_manager->reset_current_level();
}

void Game::update() {
    if (WindowShouldClose()) {
        should_exit = true;
    }

    UpdateMusicStream(vault.ui_music);

    bool ui_screen_active = current_screen == MENU || current_screen == STAGES || current_screen == KEYBINDS ||
                            current_screen == LEVEL_CLEAR || current_screen == CHAPTER_CLEAR || current_screen == GAME_COMPLETE;
    if (ui_screen_active) {
        stop_gameplay_music();
        if (!IsMusicStreamPlaying(vault.ui_music)) {
            PlayMusicStream(vault.ui_music);
        }
    } else if (IsMusicStreamPlaying(vault.ui_music)) {
        StopMusicStream(vault.ui_music);
    }

    if (current_screen == GAMEPLAY) {
        Music* gameplay_tracks[] = {
            &vault.gameplay_music_1,
            &vault.gameplay_music_2,
            &vault.gameplay_music_3,
            &vault.gameplay_music_4
        };

        if (current_gameplay_track >= 0) {
            UpdateMusicStream(*gameplay_tracks[current_gameplay_track]);
        }

        if (current_gameplay_track < 0 || !IsMusicStreamPlaying(*gameplay_tracks[current_gameplay_track])) {
            play_random_gameplay_music();
        }
    }

    if (current_screen == MENU) {
        if (IsKeyPressed(KEY_DOWN)) {
            selected_menu_option = (selected_menu_option + 1) % 4;
            PlaySound(vault.menu_switch);
        }

        if (IsKeyPressed(KEY_UP)) {
            selected_menu_option = (selected_menu_option + 3) % 4;
            PlaySound(vault.menu_switch);
        }

        if (IsKeyPressed(KEY_ENTER)) {
            if (selected_menu_option == 0) {
                reset();
                current_screen = GAMEPLAY;
            } else if (selected_menu_option == 1) {
                current_screen = STAGES;
            } else if (selected_menu_option == 2) {
                current_screen = KEYBINDS;
            } else {
                should_exit = true;
            }
        }
    }
    
    else if (current_screen == STAGES) {
        if (IsKeyPressed(KEY_DOWN)) {
            selected_chapter_option = (selected_chapter_option + 1) % 3;
            PlaySound(vault.menu_switch);
        }

        if (IsKeyPressed(KEY_UP)) {
            selected_chapter_option = (selected_chapter_option + 2) % 3;
            PlaySound(vault.menu_switch);
        }

        if (IsKeyPressed(KEY_D)) {
            selected_level_option = (selected_level_option + 1) % 3;
            PlaySound(vault.menu_switch);
        }

        if (IsKeyPressed(KEY_A)) {
            selected_level_option = (selected_level_option + 2) % 3;
            PlaySound(vault.menu_switch);
        }

        if (IsKeyPressed(KEY_ENTER)) {
            lvl_manager->current_level = selected_chapter_option * 3 + selected_level_option;
            reset();
            current_screen = GAMEPLAY;
        }

        if (IsKeyPressed(KEY_ESCAPE)) {
            current_screen = MENU;
        }
    }
    
    else if (current_screen == KEYBINDS) {
        if (IsKeyPressed(KEY_ESCAPE)) {
            current_screen = MENU;
        }
    }

    else if (current_screen == LEVEL_CLEAR) {
        handle_transition_input();
    }

    else if (current_screen == CHAPTER_CLEAR) {
        handle_transition_input();
    }

    else if (current_screen == GAME_COMPLETE) {
        handle_transition_input();
    }

    else if (current_screen == GAMEPLAY) {
        if (gameover) {
            if (IsKeyPressed(KEY_R)) {
                reset();
            }
            return;
        }

        if(my_player->hurt_timer > 0) my_player->hurt_timer--;
        if(my_player->hurt_timer > 0) my_player->is_hurt = true;
        else my_player->is_hurt = false;

        // then for void death:
        if(my_player->position.y > groundy + 300 && !my_player->is_hurt){
            my_player->lives--;
            my_player->position = {64, groundy - 250};
            my_player->yspeed = 0;
            my_player->hurt_timer = 120; // 2 seconds of invincibility
            if(my_player->lives <= 0) gameover = true;
        }

        Vector2 prev_pos = my_player->position;

        level* current_lvl = lvl_manager->get_current_level();

        Rectangle player_hitbox = {
            my_player->position.x,
            my_player->position.y,
            my_player->width,
            my_player->height
        };

        my_player->on_ladder = false;
        for(auto& rect : current_lvl->ladders){
            Rectangle expanded = {
                rect.x - 10,
                rect.y,
                rect.width + 20,
                rect.height
            };
            
            if(CheckCollisionRecs(player_hitbox, expanded)){
                if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP) || IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)){
                    my_player->on_ladder = true;
                    my_player->yspeed = 0;
                }
                break;
            }
        }
        my_player->update(groundy);

        player_hitbox = {my_player->position.x, my_player->position.y, my_player->width, my_player->height};

        for (auto obs : current_lvl->obstacles) {
            // 1. Get the exact hitbox. NO SHRINKING for solid tiles!
            Rectangle obstacle_hitbox = {
                obs->position.x,
                obs->position.y,
                obs->width,
                obs->height
            };

            if(obs->the_type == spike){
                obstacle_hitbox.x = obs->position.x;
                obstacle_hitbox.y = obs->position.y;
                obstacle_hitbox.width = obs->width;
                obstacle_hitbox.height = obs->height;
            }

            if (!CheckCollisionRecs(player_hitbox, obstacle_hitbox))
                continue;

            if(obs->is_harmful && !my_player->is_hurt){
                my_player->lives--;

                my_player->position = {64, groundy - 250};
                my_player->yspeed = 0;

                my_player->hurt_timer = 120;
                my_player->is_hurt = true; 
                if(my_player->lives <= 0) gameover = true;
                continue;
            }

            float prev_bottom = prev_pos.y + my_player->height;
            float prev_right = prev_pos.x + my_player->width;

            if (my_player->yspeed >= 0 && prev_bottom <= obstacle_hitbox.y) {
                my_player->position.y = obstacle_hitbox.y - my_player->height;
                my_player->yspeed = 0;
                my_player->on_ground = true;

                if (obs->is_moving) {
                    my_player->position.x += obs->speed * obs->direction;
                }

            } else if (my_player->yspeed < 0 && prev_pos.y >= obstacle_hitbox.y + obstacle_hitbox.height) {
                my_player->position.y = obstacle_hitbox.y + obstacle_hitbox.height;
                my_player->yspeed = 0;
            } else if (prev_right <= obstacle_hitbox.x) {
                my_player->position.x = obstacle_hitbox.x - my_player->width;
            } else if (prev_pos.x >= obstacle_hitbox.x + obstacle_hitbox.width) {
                my_player->position.x = obstacle_hitbox.x + obstacle_hitbox.width;
            }

            player_hitbox.x = my_player->position.x;
            player_hitbox.y = my_player->position.y;
        }

        for(auto& rect : current_lvl->terrain_tiles){
            if(!CheckCollisionRecs(player_hitbox, rect)) continue;
            
            float prev_bottom = prev_pos.y + my_player->height;
            
            if(my_player->yspeed >= 0 && prev_bottom <= rect.y + 16){
                my_player->position.y = rect.y - my_player->height;
                my_player->yspeed = 0;
                my_player->on_ground = true;
            } else if(my_player->yspeed < 0 && prev_pos.y >= rect.y + rect.height){
                my_player->position.y = rect.y + rect.height;
                my_player->yspeed = 0;
            } else if(prev_pos.x + my_player->width <= rect.x){
                my_player->position.x = rect.x - my_player->width;
            } else if(prev_pos.x >= rect.x + rect.width){
                my_player->position.x = rect.x + rect.width;
            }
            
            player_hitbox.x = my_player->position.x;
            player_hitbox.y = my_player->position.y;
        }

        if(CheckCollisionRecs(player_hitbox, current_lvl->goal)){
            prepare_level_transition();
            return;
        }
      

        lvl_manager->update();
        camera.target = my_player->position;

        for (auto c : current_lvl->coins) {
            if (c->collect(player_hitbox)) {
                collected_coins += c->value;
            }
        }

        if (IsKeyPressed(KEY_ESCAPE))
            current_screen = MENU;
    }
}

namespace {
void return_to_main_menu(Game& game)
{
    game.selected_menu_option = 0;
    game.current_screen = MENU;
}
}

Game::~Game(){
    delete my_player;
    delete lvl_manager;
    delete game_ui;
}

void Game::play_random_gameplay_music() {
    Music* gameplay_tracks[] = {    
        &vault.gameplay_music_1,
        &vault.gameplay_music_2,
        &vault.gameplay_music_3,
        &vault.gameplay_music_4
    };

    if (current_gameplay_track >= 0) {
        StopMusicStream(*gameplay_tracks[current_gameplay_track]);
    }

    int next_track = GetRandomValue(0, 3);
    if (current_gameplay_track >= 0 && next_track == current_gameplay_track) {
        next_track = (next_track + 1) % 4;
    }

    current_gameplay_track = next_track;
    PlayMusicStream(*gameplay_tracks[current_gameplay_track]);
}

void Game::stop_gameplay_music() {
    Music* gameplay_tracks[] = {
        &vault.gameplay_music_1,
        &vault.gameplay_music_2,
        &vault.gameplay_music_3,
        &vault.gameplay_music_4
    };

    if (current_gameplay_track >= 0 && IsMusicStreamPlaying(*gameplay_tracks[current_gameplay_track])) {
        StopMusicStream(*gameplay_tracks[current_gameplay_track]);
    }

    current_gameplay_track = -1;
}

void Game::prepare_level_transition()
{
    selected_transition_option = 0;

    int completed_level = lvl_manager->current_level;
    int next_level = completed_level + 1;

    pending_transition_title = "You Won!";
    pending_transition_story.clear();
    pending_transition_story_title.clear();

    if (completed_level >= 8) {
        pending_transition_subtitle = "You cleared the final level\n and conquered the last\n chapter.\n";
        current_screen = GAME_COMPLETE;
        return;
    }

    bool chapter_complete = (completed_level == 2 || completed_level == 5);

    if (chapter_complete) {
        int next_chapter = next_level / 3;
        pending_transition_subtitle = "The next chapter is waiting\n beyond this victory.";
        pending_transition_story_title = GAME_CHAPTERS[next_chapter].title;
        pending_transition_story = GAME_CHAPTERS[next_chapter].story;
        current_screen = CHAPTER_CLEAR;
    } else {
        pending_transition_subtitle = "Level " + std::to_string(next_level + 1) + " is ready when you are.";
        current_screen = LEVEL_CLEAR;
    }
}

void Game::advance_to_next_level()
{
    if (lvl_manager->current_level < 8) {
        lvl_manager->current_level++;
        selected_chapter_option = lvl_manager->current_level / 3;
        selected_level_option = lvl_manager->current_level % 3;
        reset();
        current_screen = GAMEPLAY;
    } else {
        current_screen = MENU;
    }
}

void Game::handle_transition_input()
{
    if (IsKeyPressed(KEY_DOWN)) {
        selected_transition_option = (selected_transition_option + 1) % 3;
        PlaySound(vault.menu_switch);
    }

    if (IsKeyPressed(KEY_UP)) {
        selected_transition_option = (selected_transition_option + 2) % 3;
        PlaySound(vault.menu_switch);
    }

    if (IsKeyPressed(KEY_ENTER)) {
        if (selected_transition_option == 0) {
            if (current_screen == GAME_COMPLETE) {
                current_screen = MENU;
            } else {
                advance_to_next_level();
            }
        } else if (selected_transition_option == 1) {
            reset();
            current_screen = GAMEPLAY;
        } else {
            return_to_main_menu(*this);
        }
    
}
}

void Game::draw() {
    BeginDrawing();
    ClearBackground(Color{30, 34, 48, 255});

    if (current_screen == MENU) {
        game_ui->draw_main_menu(selected_menu_option);
    }
    else if (current_screen == STAGES) {
        game_ui->draw_stages_menu(selected_chapter_option, selected_level_option);
    }
    else if (current_screen == KEYBINDS) {
        game_ui->draw_keybinds();
    }
    else if (current_screen == LEVEL_CLEAR) {
        game_ui->draw_transition_screen(
            pending_transition_title,
            pending_transition_subtitle,
            "",
            "",
            "Next Level",
            selected_transition_option
        );
    }
    else if (current_screen == CHAPTER_CLEAR) {
        game_ui->draw_transition_screen(
            pending_transition_title,
            pending_transition_subtitle,
            pending_transition_story_title,
            pending_transition_story,
            "Next Chapter",
            selected_transition_option
        );
    }
    else if (current_screen == GAME_COMPLETE) {
        game_ui->draw_transition_screen(
            "You Won The Game!",
            "The full journey is complete.\n Choose your next move.",
            "",
            "",
            "Main Menu",
            selected_transition_option
        );
    }
    else if (current_screen == GAMEPLAY) {
        if (!gameover) {
            level* current_level = lvl_manager->get_current_level();
            Texture2D bg_tex = (current_level->backdrop_theme == BACKDROP_WOODS_SUN || current_level->backdrop_theme == BACKDROP_WOODS_MOON) ? vault.background1 : vault.background2;
            DrawTexturePro(bg_tex, {0, 0, (float)bg_tex.width, (float)bg_tex.height}, {0, 0, (float)screen_width, (float)screen_height}, {0, 0}, 0, WHITE);

            BeginMode2D(camera);
            lvl_manager->get_current_level()->draw_background();
            lvl_manager->draw();
            my_player->Draw();
            EndMode2D();
            
            game_ui->draw_hud(my_player->lives, collected_coins);
        } else {
            game_ui->draw_game_over(collected_coins);
        }
    }

    EndDrawing();
}
