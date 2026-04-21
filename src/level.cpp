#include "../include/level.hpp"

level::level(){

}

//destructor logic
level::~level(){
    for(auto obs : obstacles) delete obs;
    for(auto c : coins) delete c;
}

//draw logic
void level::draw(){
    for(auto obs : obstacles) obs->Draw();
    for(auto c : coins) c->Draw();
    for(auto& rect : ladders){
        DrawTexturePro(
            ladder_texture,
            {0, 0, (float)ladder_texture.width, (float)ladder_texture.height},
            {rect.x, rect.y, rect.width, rect.height},
            {0, 0}, 0.0f, WHITE
        );
    }
    for(auto& rect : terrain_tiles){
        DrawTexturePro(
            terrain_texture,
            {0, 0, (float)terrain_texture.width, (float)terrain_texture.height},
            rect,
            {0, 0}, 0.0f, WHITE
        );
    }
    DrawRectangle(goal.x, goal.y, goal.width, goal.height, GREEN);
}

//update logic
void level::update(){
    for(auto obs : obstacles) obs->update();
    for(auto c : coins) c->update();
}

//loading obstacles from the map logic
void level::load_from_grid(const char** map_data, int rows, int cols, float tile_size, assets_manager& vault, float ground_y){
    ladder_texture = vault.ladder;
    box_texture = vault.box;
    terrain_texture = vault.grass;
    coin_sound = vault.coin_pickup;
    spike_texture = vault.spike;
    groundy = ground_y;

    for(auto obs : obstacles) delete obs;
    obstacles.clear();

    for(auto c : coins) delete c;
    coins.clear();

    for(int y = 0; y < rows; y++){
        int row_len = strlen(map_data[y]);
        for(int x = 0; x < row_len; x++){
            char tile = map_data[y][x];

            float spawn_x = x * tile_size;
            float spawn_y = groundy - (rows - y) * tile_size;

            if(tile == 'T'){
                terrain_tiles.push_back({spawn_x, spawn_y, tile_size, tile_size});
            } else if(tile == 'B'){
                obstacles.push_back(new obstacle(spawn_x, spawn_y, false, box, box_texture, spike_texture));
            } else if(tile == 'M'){
                obstacles.push_back(new obstacle(spawn_x, spawn_y, true, moving_pad, box_texture, spike_texture));
            } else if(tile == 'S'){
                obstacles.push_back(new obstacle(spawn_x, spawn_y, false, spike, box_texture, spike_texture));
            } else if(tile == 'C'){
                coins.push_back(new coin(spawn_x, spawn_y, 15.0f, 1, coin_sound));
            } else if(tile == 'L'){
                ladders.push_back({spawn_x, spawn_y, 32, 32});
            } else if(tile == 'G'){
                goal = {spawn_x, spawn_y, 32, 192};
                printf("Goal placed at x=%.0f y=%.0f\n", spawn_x, spawn_y);
            }
        }
    }
}  

//reset position logic
void level::reset(){
    for(auto obs : obstacles){
        obs->position.x = obs->start_x;
        obs->position.y = obs->start_y;
        obs->direction = -1;  
    }
    for(auto c : coins){
        c->collected = false;
        
    }

}