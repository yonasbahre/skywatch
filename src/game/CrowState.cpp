#include "CrowState.h"
#include "Direction.h"
#include "Utils.h"
#include "GameUtils.h"
#include <iostream>

CrowState::CrowState(Crow *crow_) {
    this->crow = crow_;
}

CrowIdleState::CrowIdleState(Crow *crow_) : CrowState(crow) {
    Direction direction = (Direction) randInt(0, 3);
    velocity = getVelocityFromDirection(direction, IDLE_SPEED);
}

void CrowIdleState::update(Crow *crow) {    
    this->crow = crow;
    if (
        crow->startPos.x + MAX_IDLE_DIST <= crow->pos.x ||
        crow->startPos.x - MAX_IDLE_DIST >= crow->pos.x ||
        crow->startPos.y + MAX_IDLE_DIST <= crow->pos.y ||
        crow->startPos.y - MAX_IDLE_DIST >= crow->pos.y  
    ) {
        velocity = velocity * Vec2D(-1, -1);
    } else if (randInt(1, 500) <= 1) {
        Direction newDirection = (Direction) randInt(0, 3);
        velocity = getVelocityFromDirection(newDirection, IDLE_SPEED);
    }

    crow->pos = crow->pos + velocity;
}

CrowGiftingPebbleState::CrowGiftingPebbleState(Crow *crow_) : CrowState(crow) {
    // TODO: implement
}

void CrowGiftingPebbleState::update(Crow *crow) {
    this->crow = crow;

    // TODO: implement
}