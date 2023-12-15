#pragma once
#include "Vec2D.h"
#include "Direction.h"

Vec2D getVelocityTowardPosition(
    Vec2D currDistance,
    Vec2D currVelocity,
    float speed
);

Vec2D getVelocityFromDirection(Direction direction, float speed);