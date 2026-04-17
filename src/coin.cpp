#include "../include/coin.hpp"

#include <cmath>

coin::coin(float x, float y, float coin_radius, int coin_value, Sound coin_pickup_sound)
{
    position = {x, y};
    radius = coin_radius;
    base_y = y;
    bob_offset = 0.0f;
    bob_speed = 3.0f;
    bob_amplitude = 8.0f;
    value = coin_value;
    collected = false;
    pickup_sound = coin_pickup_sound;
}

void coin::update()
{
    if (collected)
    {
        return;
    }

    bob_offset += GetFrameTime() * bob_speed;
    position.y = base_y + std::sin(bob_offset) * bob_amplitude;
}

void coin::Draw() const
{
    if (collected)
    {
        return;
    }

    DrawCircleV(position, radius, GOLD);
    DrawCircleLines((int)position.x, (int)position.y, radius, ORANGE);
    DrawCircleV(position, radius * 0.45f, Fade(YELLOW, 0.85f));
    DrawRectangleRounded(
        {position.x - radius * 0.12f, position.y - radius * 0.55f, radius * 0.24f, radius * 1.1f},
        0.4f,
        4,
        Color{207, 140, 30, 255});
}

bool coin::collect(const Rectangle& target)
{
    if (collected)
    {
        return false;
    }

    if (CheckCollisionRecs(get_hitbox(), target))
    {
        collected = true;
        if (pickup_sound.frameCount > 0)
        {
            PlaySound(pickup_sound);
        }
        return true;
    }

    return false;
}

void coin::reset(float x, float y)
{
    position = {x, y};
    base_y = y;
    bob_offset = 0.0f;
    collected = false;
}

Rectangle coin::get_hitbox() const
{
    return {position.x - radius, position.y - radius, radius * 2.0f, radius * 2.0f};
}
