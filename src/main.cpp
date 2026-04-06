#include "../include/player.h"
#include "../include/obstacle.h"

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
    type_of_obstacle typeofobstacle = type_of_obstacle::tall_obstacle;

    InitWindow(screen_width, screen_height, "platformer: game of the century");
    InitAudioDevice();

    SetTargetFPS(60);

    obstacle the_first_obstacle(400, groundy - 100, typeofobstacle, is_moving);
    player my_player(player_start_x, player_start_y);

    //main game loop
    while(WindowShouldClose() == false) {

        if(!gameover) {
            my_player.update(groundy - 100);
            the_first_obstacle.update();
        }


        BeginDrawing();
        ClearBackground(BLACK);
        my_player.Draw();
        the_first_obstacle.Draw();

        EndDrawing();
    }


    CloseWindow();
    return 0;
}