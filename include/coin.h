#pragma once

#include <raylib.h>

struct coin
{
    Vector2 position;
    float radius;
    float base_y;
    float bob_offset;
    float bob_speed;
    float bob_amplitude;
    int value;
    bool collected;
    Sound pickup_sound;

    coin(float x, float y, float coin_radius, int coin_value, Sound coin_pickup_sound);

    void update();
    void Draw() const;
    bool collect(const Rectangle& target);
    void reset(float x, float y);
    Rectangle get_hitbox() const;
};
