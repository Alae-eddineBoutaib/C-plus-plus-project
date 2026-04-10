#include "../include/player.h"
#include "../include/obstacle.h"
#include "../include/assets.h"

using namespace std;

int main () {

    cout << "starting the game"<<endl;
    const int screen_width = 1280;
    const int screen_height = 800;
    bool gameover = false;
    bool is_moving = true;
    int player_start_x = 150;
    int player_start_y = 150;
    float groundy = screen_height - 100 ;
    

    InitWindow(screen_width, screen_height, "platformer: game of the century");
    InitAudioDevice();

    SetTargetFPS(60);

    assets_manager vault;
    Texture2D gameover_image = LoadTexture("assets/images/gameover.png");
    obstacle the_first_obstacle(800, groundy - 100, is_moving, vault.ghost_sprite, vault.skeleton_sprite, vault.robot_sprite);
    player my_player(player_start_x, player_start_y);


    //main game loop
    while(WindowShouldClose() == false) {

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
        }

        BeginDrawing();
        ClearBackground(BLACK);
        if(!gameover){
            my_player.Draw();
            the_first_obstacle.Draw();
        } else {
            DrawTexture(gameover_image, 0, 0, WHITE);
        }
        EndDrawing();
    }


    CloseWindow();
    return 0;
}