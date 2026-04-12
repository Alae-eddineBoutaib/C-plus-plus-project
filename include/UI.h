#pragma once

#include <raylib.h>
#include <string>

struct UI
{
    int screen_width;
    int screen_height;
    int font_size;

    UI(int width, int height);

    void draw_hud(int lives, int coins) const;
    void draw_game_over(int coins) const;
    void draw_main_menu(int selected_option) const;
    void draw_stages_menu(int selected_stage) const;
    void draw_keybinds() const;

private:
    void draw_panel() const;
    void draw_text_shadow(const std::string& text, int x, int y, int size, Color color) const;
    void draw_centered_text(const std::string& text, int y, int size, Color color) const;
};
