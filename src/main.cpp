#include "../include/game.hpp"
#include "../include/assets.hpp"
#include "../include/player.hpp"
#include "../include/obstacle.hpp"  
#include "../include/coin.hpp"

int main() {
    const int screen_width = 1280;
    const int screen_height = 800;

    InitWindow(screen_width, screen_height, "platformer");
    InitAudioDevice();
    SetTargetFPS(60);
    SetExitKey(0);

    Game game(screen_width, screen_height);

    while (!WindowShouldClose() && !game.should_exit) {
        game.update();
        game.draw();
    }

    CloseWindow();
    return 0;
}