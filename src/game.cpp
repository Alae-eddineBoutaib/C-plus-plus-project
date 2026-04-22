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
            if(lvl_manager->current_level < 8){
                lvl_manager->current_level++;
                my_player->yspeed = 0;
                my_player->on_ladder = false;
                my_player->hurt_timer = 0;
                my_player->is_hurt = false;
                my_player->position = {64, groundy - 300};
                lvl_manager->reset_current_level();
            } else {
                // game won - for now just go to menu
                current_screen = MENU;
            }
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