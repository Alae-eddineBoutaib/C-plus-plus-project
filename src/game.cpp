#include "../include/game.hpp"
#include "../include/levelmanager.hpp"

Game::Game(int width, int height) {
    screen_width = width;
    screen_height = height;
    should_exit = false;

    gameover = false;
    collected_coins = 0;

    selected_menu_option = 0;
    selected_stage_option = 0;

    groundy = screen_height - 100;
    current_screen = MENU;

    my_player = new player(10, 750, vault.player_sprite_idle,
                           vault.player_sprite_run,
                           vault.player_sprite_jump,
                           vault.player_jump);

    lvl_manager = new levelmanager(vault, groundy);
    game_ui = new UI(screen_width, screen_height);

    camera.target = my_player->position;
    camera.offset = {(float)screen_width / 2, (float)screen_height / 2};
    camera.zoom = 1.0f;
}

void Game::reset() {
    gameover = false;
    collected_coins = 0;

    my_player->lives = 3;
    my_player->position = {10, 750};

    lvl_manager->reset_current_level();
}

void Game::update() {
    if (current_screen == MENU) {
        if (IsKeyPressed(KEY_DOWN))
            selected_menu_option = (selected_menu_option + 1) % 4;

        if (IsKeyPressed(KEY_UP))
            selected_menu_option = (selected_menu_option + 3) % 4;

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
        if (IsKeyPressed(KEY_DOWN))
            selected_stage_option = (selected_stage_option + 1) % 3;

        if (IsKeyPressed(KEY_UP))
            selected_stage_option = (selected_stage_option + 2) % 3;

        if (IsKeyPressed(KEY_ENTER)) {
            if (selected_stage_option == 0) {
                lvl_manager->current_level = 0;
                reset();
                current_screen = GAMEPLAY;
            } else if (selected_stage_option == 2) {
                current_screen = MENU;
            }
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

    else if (current_screen == GAMEPLAY) {
        if (gameover) {
            if (IsKeyPressed(KEY_R)) {
                reset();
            }
            return;
        }

        Vector2 prev_pos = my_player->position;

        // FIXED: Removed the on_ground = false line that was here!
        my_player->update(groundy);

        Rectangle player_hitbox = {
            my_player->position.x,
            my_player->position.y,
            my_player->width,
            my_player->height
        };

        level* current_lvl = lvl_manager->get_current_level();

        for (auto obs : current_lvl->obstacles) {
            float shrink = 0.5f;

            Rectangle obstacle_hitbox = {
                obs->position.x + (obs->width * (1 - shrink) / 2),
                obs->position.y + (obs->height * (1 - shrink) / 2),
                obs->width * shrink,
                obs->height * shrink
            };

            if (!CheckCollisionRecs(player_hitbox, obstacle_hitbox))
                continue;

            if (obs->is_harmful) {
                my_player->lives--;
                my_player->position = {10, 750};
                if (my_player->lives <= 0)
                    gameover = true;
                continue;
            }

            // FIXED: Added "my_player->yspeed >= 0" so it doesn't suck you back down when you jump
            if (my_player->yspeed >= 0 && prev_pos.y + my_player->height <= obstacle_hitbox.y) {
                my_player->position.y = obstacle_hitbox.y - my_player->height;
                my_player->yspeed = 0;
                my_player->on_ground = true;

                if (obs->is_moving) {
                    my_player->position.x += obs->speed * obs->direction;
                }
            }
            else if (prev_pos.y >= obstacle_hitbox.y + obstacle_hitbox.height) {
                my_player->position.y = obstacle_hitbox.y + obstacle_hitbox.height;
                my_player->yspeed = 0;
            }
            else {
                if (prev_pos.x + my_player->width <= obstacle_hitbox.x) {
                    my_player->position.x = obstacle_hitbox.x - my_player->width;
                } else if (prev_pos.x >= obstacle_hitbox.x + obstacle_hitbox.width) {
                    my_player->position.x = obstacle_hitbox.x + obstacle_hitbox.width;
                }
            }

            player_hitbox.x = my_player->position.x;
            player_hitbox.y = my_player->position.y;
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

Game::~Game(){
    delete my_player;
    delete lvl_manager;
    delete game_ui;
}

void Game::draw() {
    BeginDrawing();
    ClearBackground(Color{30, 34, 48, 255});

    if (current_screen == MENU) {
        game_ui->draw_main_menu(selected_menu_option);
    }
    else if (current_screen == STAGES) {
        game_ui->draw_stages_menu(selected_stage_option);
    }
    else if (current_screen == KEYBINDS) {
        game_ui->draw_keybinds();
    }
    else if (current_screen == GAMEPLAY) {
        if (!gameover) {
            BeginMode2D(camera);
            DrawRectangle(0, (int)groundy, screen_width, screen_height - (int)groundy, Color{74, 117, 44, 255});
            my_player->Draw();
            lvl_manager->draw();
            EndMode2D();
            
            game_ui->draw_hud(my_player->lives, collected_coins);
        } else {
            game_ui->draw_game_over(collected_coins);
        }
    }

    EndDrawing();
}