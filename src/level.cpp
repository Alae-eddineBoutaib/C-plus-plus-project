#include "../include/level.hpp"
#include <algorithm>

namespace {

Color make_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255) {
    return Color{r, g, b, a};
}

void draw_pixel_orb(Vector2 center, float radius, Color inner, Color outer) {
    DrawCircleV(center, radius, outer);
    DrawCircleV(center, radius * 0.7f, inner);
    DrawCircleV({center.x - radius * 0.18f, center.y - radius * 0.22f}, radius * 0.16f, Fade(WHITE, 0.45f));
}

void draw_castle_towers(float start_x, float base_y, Color color) {
    for (int i = 0; i < 4; i++) {
        float x = start_x + i * 165.0f;
        float width = (i % 2 == 0) ? 62.0f : 86.0f;
        float height = 130.0f + i * 18.0f;
        DrawRectangleV({x, base_y - height}, {width, height}, color);
        DrawRectangleV({x - 10.0f, base_y - height - 18.0f}, {width + 20.0f, 18.0f}, color);
        for (int c = 0; c < 4; c++) {
            DrawRectangleV({x + 6.0f + c * ((width - 18.0f) / 3.0f), base_y - height - 28.0f}, {10.0f, 10.0f}, color);
        }
        DrawRectangleV({x + width * 0.3f, base_y - height * 0.55f}, {width * 0.2f, height * 0.2f}, Fade(make_color(245, 214, 120), 0.3f));
    }
}

void draw_tree_line(float start_x, float base_y, int count, Color trunk, Color canopy, bool haunted) {
    for (int i = 0; i < count; i++) {
        float x = start_x + i * 96.0f;
        float height = 70.0f + (float)((i * 19) % 35);
        DrawRectangleV({x, base_y - height}, {12.0f, height}, trunk);
        DrawTriangle(
            {x - 28.0f, base_y - height + 28.0f},
            {x + 6.0f, base_y - height - 42.0f},
            {x + 40.0f, base_y - height + 28.0f},
            canopy
        );
        DrawTriangle(
            {x - 22.0f, base_y - height + 4.0f},
            {x + 6.0f, base_y - height - 54.0f},
            {x + 34.0f, base_y - height + 4.0f},
            Fade(canopy, 0.85f)
        );

        if (haunted && i % 3 == 1) {
            Vector2 ghost = {x + 44.0f, base_y - height - 16.0f - (float)(i % 2) * 12.0f};
            DrawCircleV(ghost, 12.0f, Fade(make_color(220, 235, 255), 0.7f));
            DrawRectangleV({ghost.x - 12.0f, ghost.y}, {24.0f, 18.0f}, Fade(make_color(220, 235, 255), 0.6f));
            DrawCircleV({ghost.x - 4.0f, ghost.y - 2.0f}, 1.6f, make_color(40, 45, 70));
            DrawCircleV({ghost.x + 4.0f, ghost.y - 2.0f}, 1.6f, make_color(40, 45, 70));
        }
    }
}

void draw_cave_teeth(float start_x, float top_y, float width, Color color, bool hanging) {
    for (int i = 0; i < 10; i++) {
        float x = start_x + i * (width / 10.0f);
        float tooth_width = 65.0f + (float)((i * 23) % 35);
        float tooth_height = 60.0f + (float)((i * 31) % 75);
        if (hanging) {
            DrawTriangle(
                {x, top_y},
                {x + tooth_width * 0.5f, top_y + tooth_height},
                {x + tooth_width, top_y},
                color
            );
        } else {
            DrawTriangle(
                {x, top_y},
                {x + tooth_width * 0.5f, top_y - tooth_height},
                {x + tooth_width, top_y},
                color
            );
        }
    }
}

void draw_knight_banner(float x, float y, Color pole, Color cloth, Color emblem) {
    DrawRectangleV({x, y - 120.0f}, {8.0f, 120.0f}, pole);
    DrawRectangleV({x + 8.0f, y - 110.0f}, {72.0f, 54.0f}, cloth);
    DrawTriangle(
        {x + 8.0f, y - 56.0f},
        {x + 44.0f, y - 16.0f},
        {x + 80.0f, y - 56.0f},
        cloth
    );
    DrawCircleV({x + 44.0f, y - 84.0f}, 10.0f, emblem);
    DrawLineEx({x + 44.0f, y - 98.0f}, {x + 44.0f, y - 70.0f}, 3.0f, Fade(WHITE, 0.6f));
}
}

level::level(){
    goal = {0, 0, 0, 0};
    groundy = 0.0f;
    backdrop_theme = BACKDROP_WOODS_SUN;
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
            {(float)(int)rect.x, (float)(int)rect.y, rect.width + 1, rect.height + 1},
            {0, 0}, 0.0f, WHITE
        );
    }
    DrawTexturePro(
        goal_texture,
        {0, 0, (float)goal_texture.width, (float)goal_texture.height},
        {goal.x, goal.y, goal.width, goal.height},
        {0, 0}, 0.0f, WHITE
    );
}

void level::draw_background() const {
    float scene_width = std::max(goal.x + 320.0f, 2200.0f);
    float skyline_y = groundy - 360.0f;
    float far_base_y = groundy - 96.0f;
    float near_base_y = groundy - 36.0f;

    Color sky_top = make_color(40, 44, 70);
    Color sky_bottom = make_color(90, 78, 74);
    Color far_silhouette = make_color(34, 33, 49);
    Color near_silhouette = make_color(18, 18, 30);
    Color accent = make_color(246, 197, 91);
    bool use_moon = false;
    bool haunted = false;
    bool caves = false;
    bool fortress = false;
    bool knights = false;

    switch (backdrop_theme) {
        case BACKDROP_WOODS_SUN:
            sky_top = make_color(41, 55, 85);
            sky_bottom = make_color(207, 126, 72);
            far_silhouette = make_color(45, 58, 56);
            near_silhouette = make_color(27, 35, 30);
            accent = make_color(255, 193, 92);
            break;
        case BACKDROP_WOODS_MOON:
            sky_top = make_color(25, 31, 61);
            sky_bottom = make_color(83, 76, 110);
            far_silhouette = make_color(39, 41, 66);
            near_silhouette = make_color(20, 23, 39);
            accent = make_color(214, 231, 255);
            use_moon = true;
            break;
        case BACKDROP_HAUNTED_GROVE:
            sky_top = make_color(21, 28, 55);
            sky_bottom = make_color(59, 94, 99);
            far_silhouette = make_color(30, 44, 52);
            near_silhouette = make_color(16, 27, 32);
            accent = make_color(211, 239, 255);
            use_moon = true;
            haunted = true;
            break;
        case BACKDROP_IRON_KEEP:
            sky_top = make_color(30, 36, 56);
            sky_bottom = make_color(115, 84, 66);
            far_silhouette = make_color(47, 48, 59);
            near_silhouette = make_color(25, 24, 33);
            accent = make_color(255, 178, 82);
            fortress = true;
            break;
        case BACKDROP_CRYPT_CAVES:
            sky_top = make_color(18, 22, 35);
            sky_bottom = make_color(53, 62, 75);
            far_silhouette = make_color(33, 36, 47);
            near_silhouette = make_color(14, 17, 24);
            accent = make_color(160, 212, 224);
            use_moon = true;
            caves = true;
            haunted = true;
            break;
        case BACKDROP_KNIGHT_WATCH:
            sky_top = make_color(36, 33, 62);
            sky_bottom = make_color(134, 63, 54);
            far_silhouette = make_color(51, 45, 53);
            near_silhouette = make_color(25, 22, 30);
            accent = make_color(247, 165, 70);
            fortress = true;
            knights = true;
            break;
        case BACKDROP_BLOOD_MOON:
            sky_top = make_color(28, 18, 34);
            sky_bottom = make_color(114, 35, 38);
            far_silhouette = make_color(50, 28, 39);
            near_silhouette = make_color(25, 13, 21);
            accent = make_color(226, 86, 74);
            use_moon = true;
            haunted = true;
            break;
        case BACKDROP_GHOST_HALL:
            sky_top = make_color(19, 19, 35);
            sky_bottom = make_color(79, 62, 86);
            far_silhouette = make_color(39, 34, 53);
            near_silhouette = make_color(18, 16, 27);
            accent = make_color(201, 227, 255);
            use_moon = true;
            fortress = true;
            haunted = true;
            knights = true;
            break;
        case BACKDROP_FINAL_ECLIPSE:
        default:
            sky_top = make_color(12, 9, 21);
            sky_bottom = make_color(95, 24, 32);
            far_silhouette = make_color(39, 19, 28);
            near_silhouette = make_color(15, 9, 14);
            accent = make_color(246, 126, 78);
            use_moon = true;
            haunted = true;
            caves = true;
            fortress = true;
            knights = true;
            break;
    }

    DrawRectangleGradientV(-128.0f, skyline_y, scene_width + 256.0f, groundy - skyline_y + 140.0f, sky_top, sky_bottom);

    for (int i = 0; i < 16; i++) {
        float x = 120.0f + i * 150.0f;
        float y = skyline_y + 26.0f + (float)((i * 37) % 90);
        float size = (i % 3 == 0) ? 5.0f : 3.0f;
        DrawRectangleV({x, y}, {size, size}, Fade(WHITE, use_moon ? 0.55f : 0.2f));
    }

    if (use_moon) {
        draw_pixel_orb({scene_width - 260.0f, skyline_y + 115.0f}, 54.0f, accent, Fade(accent, 0.55f));
        DrawCircleV({scene_width - 238.0f, skyline_y + 105.0f}, 50.0f, Fade(sky_top, 0.92f));
    } else {
        draw_pixel_orb({scene_width - 250.0f, skyline_y + 110.0f}, 60.0f, accent, Fade(accent, 0.5f));
    }

    for (int i = 0; i < 8; i++) {
        float x = -80.0f + i * 320.0f;
        DrawCircleV({x + 110.0f, skyline_y + 84.0f + (float)(i % 2) * 18.0f}, 34.0f, Fade(WHITE, 0.08f));
        DrawCircleV({x + 148.0f, skyline_y + 74.0f + (float)(i % 3) * 12.0f}, 28.0f, Fade(WHITE, 0.08f));
        DrawCircleV({x + 78.0f, skyline_y + 76.0f}, 24.0f, Fade(WHITE, 0.08f));
    }

    for (int i = 0; i < 6; i++) {
        float ridge_x = -120.0f + i * 420.0f;
        DrawTriangle({ridge_x, far_base_y}, {ridge_x + 170.0f, skyline_y + 170.0f}, {ridge_x + 340.0f, far_base_y}, far_silhouette);
    }

    if (fortress) {
        draw_castle_towers(180.0f, far_base_y + 10.0f, Fade(make_color(67, 68, 84), 0.85f));
        draw_castle_towers(scene_width - 820.0f, far_base_y + 20.0f, Fade(make_color(59, 60, 76), 0.8f));
    }

    if (caves) {
        draw_cave_teeth(-80.0f, skyline_y + 4.0f, scene_width + 160.0f, Fade(make_color(26, 22, 30), 0.94f), true);
        draw_cave_teeth(-60.0f, near_base_y + 28.0f, scene_width + 120.0f, Fade(make_color(20, 18, 24), 0.92f), false);
    }

    draw_tree_line(-20.0f, near_base_y + 20.0f, 26, Fade(make_color(44, 30, 28), 0.95f), Fade(make_color(26, 35, 31), haunted ? 0.9f : 1.0f), haunted);

    if (knights) {
        draw_knight_banner(240.0f, near_base_y + 10.0f, make_color(94, 88, 82), make_color(112, 34, 35), make_color(238, 220, 180));
        draw_knight_banner(scene_width - 420.0f, near_base_y + 10.0f, make_color(94, 88, 82), make_color(73, 83, 126), make_color(238, 220, 180));
        DrawRectangleV({scene_width * 0.5f - 18.0f, near_base_y - 84.0f}, {36.0f, 84.0f}, Fade(make_color(44, 44, 58), 0.95f));
        DrawCircleV({scene_width * 0.5f, near_base_y - 98.0f}, 18.0f, Fade(make_color(150, 151, 166), 0.9f));
        DrawLineEx({scene_width * 0.5f, near_base_y - 82.0f}, {scene_width * 0.5f, near_base_y - 24.0f}, 6.0f, Fade(make_color(150, 151, 166), 0.9f));
        DrawLineEx({scene_width * 0.5f - 26.0f, near_base_y - 54.0f}, {scene_width * 0.5f + 26.0f, near_base_y - 54.0f}, 6.0f, Fade(make_color(150, 151, 166), 0.9f));
    }

    DrawRectangleV({-64.0f, groundy}, {scene_width + 128.0f, 220.0f}, make_color(16, 18, 22));
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
    goal_texture = vault.goal;
    groundy = ground_y;
    this->vault = &vault;

    for(auto obs : obstacles) delete obs;
    obstacles.clear();

    for(auto c : coins) delete c;
    coins.clear();
    ladders.clear();
    terrain_tiles.clear();
    goal = {0, 0, 0, 0};

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
                ladders.push_back({spawn_x, spawn_y - tile_size * 2, tile_size, tile_size});
            } else if(tile == 'G'){
                goal = {spawn_x, spawn_y - 32, 48, 96};
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

void level::set_backdrop_theme(int theme) {
    backdrop_theme = theme;
}