#include "../include/UI.hpp"

UI::UI(int width, int height)
{
    screen_width = width;
    screen_height = height;
    font_size = 30;
}

void UI::draw_hud(int lives, int coins) const
{
    draw_panel();
    draw_text_shadow("Lives: " + std::to_string(lives), 20, 18, font_size, RAYWHITE);
    draw_text_shadow("Coins: " + std::to_string(coins), 220, 18, font_size, GOLD);
}

void UI::draw_game_over(int coins) const
{
    DrawRectangle(0, 0, screen_width, screen_height, Fade(BLACK, 0.7f));

    const std::string game_over = "GAME OVER";
    const std::string coins_text = "Coins collected: " + std::to_string(coins);
    const std::string retry_text = "Press R to play again";

    int game_over_x = (screen_width - MeasureText(game_over.c_str(), 64)) / 2;
    int coins_x = (screen_width - MeasureText(coins_text.c_str(), 32)) / 2;
    int retry_x = (screen_width - MeasureText(retry_text.c_str(), 26)) / 2;

    draw_text_shadow(game_over, game_over_x, screen_height / 2 - 100, 64, RED);
    draw_text_shadow(coins_text, coins_x, screen_height / 2, 32, GOLD);
    draw_text_shadow(retry_text, retry_x, screen_height / 2 + 60, 26, RAYWHITE);
}

void UI::draw_main_menu(int selected_option) const
{
    const char* options[4] = {"Start Game", "Stages", "Keybinds", "Quit"};

    DrawRectangleGradientV(0, 0, screen_width, screen_height, Color{26, 31, 53, 255}, Color{10, 14, 24, 255});
    DrawCircle(screen_width - 180, 140, 110.0f, Fade(GOLD, 0.10f));
    DrawCircle(160, screen_height - 130, 140.0f, Fade(SKYBLUE, 0.08f));

    draw_centered_text("PLATFORMER", 110, 64, RAYWHITE);
    draw_centered_text("Use UP/DOWN and ENTER", 190, 24, Fade(RAYWHITE, 0.8f));

    for (int i = 0; i < 4; i++)
    {
        Rectangle button = {(float)screen_width / 2.0f - 180.0f, 270.0f + (float)i * 90.0f, 360.0f, 64.0f};
        bool selected = i == selected_option;
        Color fill = selected ? Color{220, 179, 55, 255} : Fade(RAYWHITE, 0.10f);
        Color border = selected ? GOLD : Fade(RAYWHITE, 0.35f);
        Color text_color = selected ? BLACK : RAYWHITE;

        DrawRectangleRounded(button, 0.25f, 8, fill);
        DrawRectangleLinesEx(button, 2.0f, border);
        draw_centered_text(options[i], (int)button.y + 18, 30, text_color);
    }
}

void UI::draw_stages_menu(int selected_stage) const
{
    const char* stages[3] = {"Stage 1 - Forest Path", "Stage 2 - Locked", "Back"};

    DrawRectangleGradientV(0, 0, screen_width, screen_height, Color{24, 42, 28, 255}, Color{9, 18, 11, 255});
    draw_centered_text("STAGES", 90, 58, RAYWHITE);
    draw_centered_text("Only Stage 1 is playable right now", 165, 26, Fade(RAYWHITE, 0.8f));

    for (int i = 0; i < 3; i++)
    {
        Rectangle card = {(float)screen_width / 2.0f - 230.0f, 255.0f + (float)i * 95.0f, 460.0f, 68.0f};
        bool selected = i == selected_stage;
        Color fill = selected ? Color{119, 181, 79, 255} : Fade(RAYWHITE, 0.08f);
        Color border = selected ? LIME : Fade(RAYWHITE, 0.30f);
        Color text_color = selected ? BLACK : RAYWHITE;

        DrawRectangleRounded(card, 0.20f, 8, fill);
        DrawRectangleLinesEx(card, 2.0f, border);
        draw_centered_text(stages[i], (int)card.y + 20, 28, text_color);
    }

    draw_centered_text("Press ESC to return", screen_height - 80, 22, Fade(RAYWHITE, 0.75f));
}

void UI::draw_keybinds() const
{
    DrawRectangleGradientV(0, 0, screen_width, screen_height, Color{44, 29, 24, 255}, Color{15, 10, 8, 255});
    draw_centered_text("KEYBINDS", 90, 58, RAYWHITE);

    DrawRectangleRounded({screen_width / 2.0f - 270.0f, 220.0f, 540.0f, 280.0f}, 0.18f, 8, Fade(BLACK, 0.35f));
    DrawRectangleLinesEx({screen_width / 2.0f - 270.0f, 220.0f, 540.0f, 280.0f}, 2.0f, Fade(RAYWHITE, 0.30f));

    draw_text_shadow("A  - Move Left", screen_width / 2 - 210, 270, 30, RAYWHITE);
    draw_text_shadow("D  - Move Right", screen_width / 2 - 210, 320, 30, RAYWHITE);
    draw_text_shadow("SPACE  - Jump", screen_width / 2 - 210, 370, 30, RAYWHITE);
    draw_text_shadow("R  - Restart After Game Over", screen_width / 2 - 210, 420, 30, GOLD);

    draw_centered_text("Press ESC to return", screen_height - 80, 22, Fade(RAYWHITE, 0.75f));
}

void UI::draw_panel() const
{
    DrawRectangleRounded({10, 10, 360, 56}, 0.25f, 8, Fade(BLACK, 0.45f));
    DrawRectangleLinesEx({10, 10, 360, 56}, 2.0f, Fade(RAYWHITE, 0.35f));
}

void UI::draw_text_shadow(const std::string& text, int x, int y, int size, Color color) const
{
    DrawText(text.c_str(), x + 2, y + 2, size, Fade(BLACK, 0.7f));
    DrawText(text.c_str(), x, y, size, color);
}

void UI::draw_centered_text(const std::string& text, int y, int size, Color color) const
{
    int x = (screen_width - MeasureText(text.c_str(), size)) / 2;
    draw_text_shadow(text, x, y, size, color);
}
