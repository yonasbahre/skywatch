#pragma once

struct Vec2D {
    float x = 0;
    float y = 0;

    Vec2D(float _x, float _y);
    Vec2D operator + (Vec2D other);
    Vec2D operator - (Vec2D other);
    Vec2D operator * (Vec2D other);
    Vec2D operator / (Vec2D other);
};