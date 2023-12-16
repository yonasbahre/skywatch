#include <chrono>
#include "EnemyState.h"
#include "Utils.h"
#include "GameUtils.h"
#include "Crow.h"

EnemyState::EnemyState(Enemy &enemy_) : enemy(enemy_) {}

EnemyIdleState::EnemyIdleState(Enemy &enemy_) : EnemyState(enemy_) {
    Enemy::attackingEnemies.erase(&enemy);
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
    Enemy::attackingEnemies.insert(&enemy);
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

    velocity = getVelocityTowardPosition(playerDistance, velocity, ATTACK_SPEED);
    enemy.pos = enemy.pos - velocity;
}

EnemyCooldownState::EnemyCooldownState(Enemy &enemy_) : EnemyState(enemy_) {
    using namespace std::chrono;
    Enemy::attackingEnemies.erase(&enemy);

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

EnemyFollowingCrowState::EnemyFollowingCrowState(Enemy &enemy_, Crow *crow_)
    : EnemyState(enemy_) {
    this->crow = crow_;
    Vec2D dist = enemy.pos - crow_->pos;
    Enemy::attackingEnemies.erase(&enemy);
    velocity = getVelocityTowardPosition(dist, {1, 1}, SPEED);
}

EnemyFollowingCrowState::EnemyFollowingCrowState(Enemy &enemy_, Crow *crow_, Vec2D targetPos)
    : EnemyState(enemy_) {
    this->crow = crow_;
    this->targetPos = targetPos;
    useTargetPos = true;
    Vec2D dist = targetPos - crow_->pos;
    Enemy::attackingEnemies.erase(&enemy);
    velocity = getVelocityTowardPosition(dist, {1, 1}, SPEED);
}

void EnemyFollowingCrowState::update() {
    if (useTargetPos) {
        Vec2D dist = enemy.pos - targetPos;

        if (std::abs(dist.x) <= STOP_DIST && std::abs(dist.y) <= STOP_DIST) {
            enemy.setState(new EnemyIdleState(enemy));
            return;
        }

        velocity = getVelocityTowardPosition(dist, velocity, SPEED);
        enemy.pos = enemy.pos - velocity;
        return;
    }

    Vec2D dist = enemy.pos - crow->pos;
    velocity = getVelocityTowardPosition(dist, velocity, SPEED);
    enemy.pos = enemy.pos - velocity;
}