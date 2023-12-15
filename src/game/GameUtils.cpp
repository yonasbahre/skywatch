#include "GameUtils.h"
#include <cmath>

Vec2D getVelocityTowardPosition(
    Vec2D currDistance,
    Vec2D currVelocity,
    float speed
) {
    bool xSignsMatch = 
        currDistance.x < 0 == currVelocity.x < 0 &&
        (currDistance.x == 0) == (currVelocity.x == 0) &&
        currDistance.x > 0 == currVelocity.x > 0;
    bool ySignsMatch =
        currDistance.y < 0 == currVelocity.y < 0 &&
        (currDistance.y == 0) == (currVelocity.y == 0) &&
        currDistance.y > 0 == currVelocity.y > 0;

    if ((!xSignsMatch && currVelocity.x != 0) || (!ySignsMatch && currVelocity.y != 0)) {
        if (std::abs(currDistance.x) > std::abs(currDistance.y)) {
            float directionSign = currDistance.x < 0 ? -1 : 1;
            currVelocity = {directionSign * speed, 0};
        } else {
            float directionSign = currDistance.y < 0 ? -1 : 1;
            currVelocity = {0, directionSign * speed};
        }
    }

    return currVelocity;
}

Vec2D getVelocityFromDirection(Direction direction, float speed) {
    switch (direction) {
        case UP:
            return {0, speed};
        case DOWN:
            return {0, -speed};
        case LEFT:
            return {-speed, 0};
        case RIGHT:
            return {speed, 0};
        default:
            return {speed, 0};
    }
}