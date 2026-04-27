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
    void draw_stages_menu(int selected_chapter, int selected_level) const;
    void draw_keybinds() const;
    void draw_transition_screen(const std::string& title,
                                const std::string& subtitle,
                                const std::string& story_title,
                                const std::string& story,
                                const char* continue_label,
                                int selected_option) const;

private:
    void draw_panel() const;
    void draw_text_shadow(const std::string& text, int x, int y, int size, Color color) const;
    void draw_centered_text(const std::string& text, int y, int size, Color color) const;
    void draw_story_block(const Rectangle& bounds, const std::string& title, const std::string& story) const;
    void draw_option_button(const Rectangle& bounds, const std::string& label, bool selected, Color accent) const;
};
