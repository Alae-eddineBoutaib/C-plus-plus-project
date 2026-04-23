#include "../include/UI.hpp"
#include <sstream>
#include <vector>

namespace {
struct ChapterInfo {
    const char* title;
    const char* levels[3];
    const char* story;
    Color accent;
};

const ChapterInfo CHAPTERS[3] = {
    {
        "Chapter I - Whispering Woods",
        {"Level 1 - Forest Path", "Level 2 - Thorn Crossing", "Level 3 - Hunter's Rise"},
        "The journey begins beneath ancient trees where the hero follows a fading trail. Every jump through the forest reveals that something dark has started to wake beyond the roots.",
        Color{114, 191, 108, 255}
    },
    {
        "Chapter II - Iron Ascent",
        {"Level 4 - Ladder Keep", "Level 5 - Rusted Watch", "Level 6 - Broken Lift"},
        "Past the forest waits a ruined stronghold of ladders, traps, and narrow ledges. The climb is no longer about discovery, but survival against a fortress that refuses to fall quietly.",
        Color{242, 179, 66, 255}
    },
    {
        "Chapter III - Crown of Shadows",
        {"Level 7 - Ash Steps", "Level 8 - Blade Hall", "Level 9 - Final Gate"},
        "At the summit, the path turns cruel and every mistake carries weight. The last chapter tests whether the hero can cross the shadowed crown and reach the gate before hope runs out.",
        Color{226, 92, 92, 255}
    }
};

std::vector<std::string> wrap_text(const std::string& text, int font_size, int max_width)
{
    std::istringstream stream(text);
    std::vector<std::string> lines;
    std::string word;
    std::string current_line;

    while (stream >> word)
    {
        std::string candidate = current_line.empty() ? word : current_line + " " + word;
        if (MeasureText(candidate.c_str(), font_size) <= max_width)
        {
            current_line = candidate;
        }
        else
        {
            if (!current_line.empty())
            {
                lines.push_back(current_line);
            }
            current_line = word;
        }
    }

    if (!current_line.empty())
    {
        lines.push_back(current_line);
    }

    return lines;
}
}

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
    const char* options[4] = {"Start Game", "Chapters", "Keybinds", "Quit"};

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

void UI::draw_stages_menu(int selected_chapter, int selected_level) const
{
    const ChapterInfo& active_chapter = CHAPTERS[selected_chapter];

    DrawRectangleGradientV(0, 0, screen_width, screen_height, Color{18, 23, 42, 255}, Color{6, 10, 20, 255});
    DrawCircle(135, 120, 90.0f, Fade(active_chapter.accent, 0.10f));
    DrawCircle(screen_width - 140, screen_height - 110, 130.0f, Fade(SKYBLUE, 0.06f));

    draw_centered_text("CHAPTER SELECT", 58, 54, RAYWHITE);
    draw_centered_text("UP/DOWN: Chapter   A/D: Level   ENTER: Play", 118, 22, Fade(RAYWHITE, 0.82f));

    for (int i = 0; i < 3; i++)
    {
        const bool chapter_selected = i == selected_chapter;
        Rectangle chapter_card = {70.0f, 200.0f + (float)i * 120.0f, 410.0f, 94.0f};
        Color fill = chapter_selected ? Fade(CHAPTERS[i].accent, 0.90f) : Fade(RAYWHITE, 0.07f);
        Color border = chapter_selected ? CHAPTERS[i].accent : Fade(RAYWHITE, 0.22f);
        Color text_color = chapter_selected ? BLACK : RAYWHITE;

        DrawRectangleRounded(chapter_card, 0.18f, 8, fill);
        DrawRectangleLinesEx(chapter_card, 2.0f, border);
        draw_text_shadow(CHAPTERS[i].title, (int)chapter_card.x + 18, (int)chapter_card.y + 16, 26, text_color);

        for (int level = 0; level < 3; level++)
        {
            Rectangle level_chip = {
                chapter_card.x + 18.0f + level * 124.0f,
                chapter_card.y + 50.0f,
                112.0f,
                28.0f
            };

            bool level_selected = chapter_selected && level == selected_level;
            Color chip_fill = level_selected ? Fade(BLACK, 0.85f) : Fade(BLACK, 0.25f);
            Color chip_border = level_selected ? RAYWHITE : Fade(RAYWHITE, 0.18f);
            Color chip_text = RAYWHITE;

            DrawRectangleRounded(level_chip, 0.30f, 8, chip_fill);
            DrawRectangleLinesEx(level_chip, 1.5f, chip_border);
            DrawText(TextFormat("Level %d", i * 3 + level + 1), (int)level_chip.x + 23, (int)level_chip.y + 5, 18, chip_text);
        }
    }

    Rectangle story_panel = {530.0f, 200.0f, 470.0f, 334.0f};
    draw_story_block(story_panel, active_chapter.title, active_chapter.story);

    DrawRectangleRounded({530.0f, 554.0f, 470.0f, 118.0f}, 0.18f, 8, Fade(BLACK, 0.28f));
    DrawRectangleLinesEx({530.0f, 554.0f, 470.0f, 118.0f}, 2.0f, Fade(active_chapter.accent, 0.75f));
    draw_text_shadow("Selected Mission", 554, 570, 24, active_chapter.accent);
    draw_text_shadow(active_chapter.levels[selected_level], 554, 606, 28, RAYWHITE);
    draw_text_shadow("Press ENTER to jump into this level.", 554, 642, 20, Fade(RAYWHITE, 0.82f));

    draw_centered_text("Press ESC to return", screen_height - 46, 20, Fade(RAYWHITE, 0.75f));
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

void UI::draw_transition_screen(const std::string& title,
                                const std::string& subtitle,
                                const std::string& story_title,
                                const std::string& story,
                                const char* continue_label,
                                int selected_option) const
{
    Color accent = story.empty() ? Color{87, 185, 242, 255} : GOLD;

    DrawRectangleGradientV(0, 0, screen_width, screen_height, Color{21, 26, 48, 255}, Color{8, 11, 22, 255});
    DrawCircle(150, 120, 90.0f, Fade(accent, 0.10f));
    DrawCircle(screen_width - 160, screen_height - 120, 150.0f, Fade(SKYBLUE, 0.08f));

    Rectangle hero_panel = {80.0f, 150.0f, 500.0f, 380.0f};
    DrawRectangleRounded(hero_panel, 0.18f, 8, Fade(BLACK, 0.28f));
    DrawRectangleLinesEx(hero_panel, 2.0f, Fade(accent, 0.75f));

    draw_text_shadow(title, 110, 195, 48, RAYWHITE);
    draw_text_shadow(subtitle, 110, 265, 28, Fade(RAYWHITE, 0.88f));
    draw_text_shadow("Choose what to do next.", 110, 320, 24, Fade(RAYWHITE, 0.74f));

    draw_option_button({110.0f, 390.0f, 180.0f, 58.0f}, continue_label, selected_option == 0, accent);
    draw_option_button({310.0f, 390.0f, 180.0f, 58.0f}, "Try Again", selected_option == 1, accent);
    draw_option_button({210.0f, 465.0f, 180.0f, 58.0f}, "Quit", selected_option == 2, accent);

    if (!story.empty())
    {
        Rectangle story_panel = {640.0f, 150.0f, 520.0f, 430.0f};
        draw_story_block(story_panel, story_title, story);
    }
    else
    {
        Rectangle info_panel = {640.0f, 150.0f, 520.0f, 430.0f};
        DrawRectangleRounded(info_panel, 0.18f, 8, Fade(BLACK, 0.28f));
        DrawRectangleLinesEx(info_panel, 2.0f, Fade(RAYWHITE, 0.22f));
        draw_text_shadow("Victory", 670, 190, 34, accent);
        draw_text_shadow("You cleared the path ahead.", 670, 250, 28, RAYWHITE);
        draw_text_shadow("Take the next level,", 670, 320, 28, Fade(RAYWHITE, 0.86f));
        draw_text_shadow("retry this one,", 670, 360, 28, Fade(RAYWHITE, 0.86f));
        draw_text_shadow("or head back out.", 670, 400, 28, Fade(RAYWHITE, 0.86f));
    }

    draw_centered_text("UP/DOWN: Move   ENTER: Confirm", screen_height - 52, 20, Fade(RAYWHITE, 0.76f));
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

void UI::draw_story_block(const Rectangle& bounds, const std::string& title, const std::string& story) const
{
    DrawRectangleRounded(bounds, 0.18f, 8, Fade(BLACK, 0.28f));
    DrawRectangleLinesEx(bounds, 2.0f, Fade(RAYWHITE, 0.22f));

    draw_text_shadow("Story", (int)bounds.x + 24, (int)bounds.y + 24, 28, RAYWHITE);
    draw_text_shadow(title, (int)bounds.x + 24, (int)bounds.y + 66, 24, GOLD);

    const int story_font_size = 24;
    const int line_height = 30;
    int text_x = (int)bounds.x + 24;
    int text_y = (int)bounds.y + 108;
    int max_width = (int)bounds.width - 48;
    std::vector<std::string> lines = wrap_text(story, story_font_size, max_width);

    for (size_t i = 0; i < lines.size(); i++)
    {
        draw_text_shadow(lines[i], text_x, text_y + (int)i * line_height, story_font_size, Fade(RAYWHITE, 0.92f));
    }
}

void UI::draw_option_button(const Rectangle& bounds, const std::string& label, bool selected, Color accent) const
{
    Color fill = selected ? accent : Fade(RAYWHITE, 0.08f);
    Color border = selected ? accent : Fade(RAYWHITE, 0.22f);
    Color text_color = selected ? BLACK : RAYWHITE;

    DrawRectangleRounded(bounds, 0.24f, 8, fill);
    DrawRectangleLinesEx(bounds, 2.0f, border);

    int label_x = (int)(bounds.x + (bounds.width - MeasureText(label.c_str(), 24)) / 2.0f);
    int label_y = (int)bounds.y + 16;
    draw_text_shadow(label, label_x, label_y, 24, text_color);
}
