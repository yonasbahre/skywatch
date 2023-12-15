#include <chrono>
#include "EnemyState.h"
#include "Utils.h"
#include "GameUtils.h"

EnemyState::EnemyState(Enemy &enemy_) : enemy(enemy_) {}

EnemyIdleState::EnemyIdleState(Enemy &enemy_) : EnemyState(enemy_) {
    Direction direction = (Direction) randInt(0, 3);
    velocity = getVelocityFromDirection(direction, IDLE_SPEED);
}

void EnemyIdleState::update() {
    Vec2D playerDistance = enemy.getPlayerDistance();
    if (
        std::abs(playerDistance.x) <= enemy.attackDistance &&
        std::abs(playerDistance.y) <= enemy.attackDistance 
    ) {
        enemy.setState(new EnemyAttackState(enemy));
        return;
    }
    
    if (
        enemy.startPos.x + MAX_IDLE_DIST <= enemy.pos.x ||
        enemy.startPos.x - MAX_IDLE_DIST >= enemy.pos.x ||
        enemy.startPos.y + MAX_IDLE_DIST <= enemy.pos.y ||
        enemy.startPos.y - MAX_IDLE_DIST >= enemy.pos.y  
    ) {
        velocity = velocity * Vec2D(-1, -1);
    } else if (randInt(1, 500) <= 1) {
        Direction newDirection = (Direction) randInt(0, 3);
        velocity = getVelocityFromDirection(newDirection, IDLE_SPEED);
    }

    enemy.pos = enemy.pos + velocity;
}


EnemyAttackState::EnemyAttackState(Enemy &enemy_) : EnemyState(enemy_) {    
    Vec2D playerDistance = enemy.getPlayerDistance();
    velocity = getVelocityTowardPosition(playerDistance, {1, 1}, ATTACK_SPEED);
}

void EnemyAttackState::update() {
    Vec2D playerDistance = enemy.getPlayerDistance();
    if (
        std::abs(playerDistance.x) > enemy.attackDistance ||
        std::abs(playerDistance.y) > enemy.attackDistance 
    ) {
        enemy.setState(new EnemyIdleState(enemy));
        return;
    }

    // bool xSignsMatch = 
    //     playerDistance.x < 0 == velocity.x < 0 &&
    //     (playerDistance.x == 0) == (velocity.x == 0) &&
    //     playerDistance.x > 0 == velocity.x > 0;
    // bool ySignsMatch =
    //     playerDistance.y < 0 == velocity.y < 0 &&
    //     (playerDistance.y == 0) == (velocity.y == 0) &&
    //     playerDistance.y > 0 == velocity.y > 0;

    // if ((!xSignsMatch && velocity.x != 0) || (!ySignsMatch && velocity.y != 0)) {
    //     if (std::abs(playerDistance.x) > std::abs(playerDistance.y)) {
    //         float directionSign = playerDistance.x < 0 ? -1 : 1;
    //         velocity = {directionSign * ATTACK_SPEED, 0};
    //     } else {
    //         float directionSign = playerDistance.y < 0 ? -1 : 1;
    //         velocity = {0, directionSign * ATTACK_SPEED};
    //     }
    // }

    velocity = getVelocityTowardPosition(playerDistance, velocity, ATTACK_SPEED);
    enemy.pos = enemy.pos - velocity;
}

EnemyCooldownState::EnemyCooldownState(Enemy &enemy_) : EnemyState(enemy_) {
    using namespace std::chrono;

    // Move enemy away from player so colliders are no longer touching
    Vec2D playerDistance = enemy.getPlayerDistance();
    Vec2D diff = {
        playerDistance.x < 0 ? -1.0f : 1.0f,
        playerDistance.y < 0 ? -1.0f : 1.0f   
    };
    enemy.pos = enemy.pos + diff;

    milliseconds now = duration_cast<milliseconds>(
        system_clock::now().time_since_epoch()
    );
    endCooldownTime = now.count() + COOLDOWN_MILLISECONDS;
}

void EnemyCooldownState::update() {
    using namespace std::chrono;

    milliseconds now = duration_cast<milliseconds>(
        system_clock::now().time_since_epoch()
    );
    if (now.count() >= endCooldownTime) {
        enemy.setState(new EnemyIdleState(enemy));
        return;
    }
}