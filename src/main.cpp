#include "../include/player.h"
#include "../include/obstacle.h"
#include "../include/assets.h"
#include "../include/coin.h"
#include "../include/UI.h"

using namespace std;

enum ScreenState { MENU, STAGES, KEYBINDS, GAMEPLAY };
int main () {

    cout << "starting the game"<<endl;
    const int screen_width = 1280;
    const int screen_height = 800;
    bool gameover = false;
    bool is_moving = true;
    int collected_coins = 0;
    int selected_menu_option = 0;
    int selected_stage_option = 0;
    int player_start_x = 10;
    int player_start_y = 750;
    float groundy = screen_height - 100;
    ScreenState current_screen = MENU;

    InitWindow(screen_width, screen_height, "platformer: game of the century");
    InitAudioDevice();

    SetExitKey(0); 

    SetTargetFPS(60);

    {
        assets_manager vault;
        obstacle the_first_obstacle(800, groundy, is_moving, vault.enemy_1, vault.enemy_2, vault.enemy_3);
        cout << "Obstacle height: " << the_first_obstacle.height << endl;
        cout << "Obstacle y: " << the_first_obstacle.position.y << endl;
        cout << "Ground y: " << groundy << endl;
        player my_player(player_start_x, player_start_y, vault.player_sprite_idle, vault.player_sprite_run, vault.player_sprite_jump, vault.player_jump);
        coin level_coin(420.0f, groundy - 80.0f, 18.0f, 1, vault.coin_pickup);
        UI game_ui(screen_width, screen_height);
        Camera2D camera = {0};
        camera.target = my_player.position;
        camera.offset = {(float) screen_width / 2,(float) screen_height / 2};
        camera.zoom = 1.0f;

        auto reset_game = [&]() {
            gameover = false;
            collected_coins = 0;
            my_player.lives = 3;
            my_player.position.x = player_start_x;
            my_player.position.y = player_start_y;
            the_first_obstacle.position.x = 800;
            the_first_obstacle.position.y = groundy - 50;
            the_first_obstacle.direction = -1;
            level_coin.reset(420.0f, groundy - 80.0f);
        };

        //main game loop
        while(WindowShouldClose() == false) {

            if (current_screen == MENU) {
                if (IsKeyPressed(KEY_DOWN)) {
                    selected_menu_option = (selected_menu_option + 1) % 4;
                }
                if (IsKeyPressed(KEY_UP)) {
                    selected_menu_option = (selected_menu_option + 3) % 4;
                }
                if (IsKeyPressed(KEY_ENTER)) {
                    if (selected_menu_option == 0) {
                        reset_game();
                        current_screen = GAMEPLAY;
                    } else if (selected_menu_option == 1) {
                        current_screen = STAGES;
                    } else if (selected_menu_option == 2) {
                        current_screen = KEYBINDS;
                    } else if (selected_menu_option == 3) {
                        break;
                    }
                }
            }
            else if (current_screen == STAGES) {
                if (IsKeyPressed(KEY_DOWN)) {
                    selected_stage_option = (selected_stage_option + 1) % 3;
                }
                if (IsKeyPressed(KEY_UP)) {
                    selected_stage_option = (selected_stage_option + 2) % 3;
                }
                if (IsKeyPressed(KEY_ESCAPE)) {
                    current_screen = MENU;
                }
                if (IsKeyPressed(KEY_ENTER)) {
                    if (selected_stage_option == 0) {
                        reset_game();
                        current_screen = GAMEPLAY;
                    } else if (selected_stage_option == 1) {
                        selected_stage_option = 1;
                    } else {
                        current_screen = MENU;
                    }
                }
            }
            else if (current_screen == KEYBINDS) {
                if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_ENTER)) {
                    current_screen = MENU;
                }
            }
            else if (current_screen == GAMEPLAY) {
                Rectangle player_hitbox = {my_player.position.x,my_player.position.y, my_player.width , my_player.height};
                Rectangle obstacle_hitbox = {the_first_obstacle.position.x, the_first_obstacle.position.y,
                                            the_first_obstacle.width, the_first_obstacle.height};

                if(CheckCollisionRecs(player_hitbox, obstacle_hitbox)){
                    my_player.lives -= 1;
                    my_player.position.x = player_start_x;
                    my_player.position.y = player_start_y;
                    if(my_player.lives == 0){
                        gameover = true;
                    }
                }

                if(!gameover){
                    my_player.update(groundy);
                    the_first_obstacle.update();
                    level_coin.update();
                    camera.target = my_player.position;

                    if(level_coin.collect(player_hitbox)){
                        collected_coins += level_coin.value;
                    }
                } else if (IsKeyPressed(KEY_R)) {
                    reset_game();
                }

                if (IsKeyPressed(KEY_ESCAPE)) {
                    current_screen = MENU;
                }
            }

            BeginDrawing();
            ClearBackground(Color{30, 34, 48, 255});

            if (current_screen == MENU) {
                game_ui.draw_main_menu(selected_menu_option);
            } else if (current_screen == STAGES) {
                game_ui.draw_stages_menu(selected_stage_option);
            } else if (current_screen == KEYBINDS) {
                game_ui.draw_keybinds();
            } else if(!gameover){
                BeginMode2D(camera);

                DrawRectangle(0, (int)groundy, screen_width, screen_height - (int)groundy, Color{74, 117, 44, 255});
                my_player.Draw();
                the_first_obstacle.Draw();
                level_coin.Draw();
                //to be deleted
                DrawRectangleLines(
                    the_first_obstacle.position.x,
                    the_first_obstacle.position.y,
                    the_first_obstacle.width,
                    the_first_obstacle.height,
                    RED
                );

                EndMode2D();
                game_ui.draw_hud(my_player.lives, collected_coins);
                DrawText("ESC - Menu", screen_width - 170, 20, 24, RAYWHITE);
            } else {
                DrawRectangle(0, 0, screen_width, screen_height, Color{30, 34, 48, 255});
                game_ui.draw_game_over(collected_coins);
            }
            EndDrawing();
        }
    } 
        CloseWindow();   
    return 0;
}
