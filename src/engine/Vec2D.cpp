#include "Vec2D.h"

Vec2D::Vec2D(float _x, float _y) : x(_x), y(_y) {}

Vec2D Vec2D::operator + (Vec2D other) {
    return Vec2D(x + other.x, y + other.y);
}

Vec2D Vec2D::operator - (Vec2D other) {
    return Vec2D(x - other.x, y - other.y);
}

Vec2D Vec2D::operator * (Vec2D other) {
    return Vec2D(x * other.x, y * other.y);
}

Vec2D Vec2D::operator / (Vec2D other) {
    return Vec2D(x / other.x, y / other.y);
}
