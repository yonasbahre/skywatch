#include "EnemyState.h"
#include "Utils.h"

EnemyState::EnemyState(Enemy &enemy_) : enemy(enemy_) {}

EnemyIdleState::EnemyIdleState(Enemy &enemy_) : EnemyState(enemy_) {
    direction = (Direction) randInt(0, 3);
    velocity = getVelocityFromDirection(direction);
}

void EnemyIdleState::update() {
    if (
        enemy.startPos.x + MAX_IDLE_DIST <= enemy.pos.x ||
        enemy.startPos.x - MAX_IDLE_DIST >= enemy.pos.x ||
        enemy.startPos.y + MAX_IDLE_DIST <= enemy.pos.y ||
        enemy.startPos.y - MAX_IDLE_DIST >= enemy.pos.y  
    ) {
        velocity = velocity * Vec2D(-1, -1);
    }

    enemy.pos = enemy.pos + velocity;
}

Vec2D EnemyIdleState::getVelocityFromDirection(Direction direction) {
    switch (direction) {
        case UP:
            return {0, IDLE_SPEED};
        case DOWN:
            return {0, -IDLE_SPEED};
        case LEFT:
            return {-IDLE_SPEED, 0};
        case RIGHT:
            return {IDLE_SPEED, 0};
        default:
            return {IDLE_SPEED, 0};
    }
}