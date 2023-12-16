#include "CrowState.h"
#include "Direction.h"
#include "Utils.h"
#include "GameUtils.h"
#include "Enemy.h"
#include "EnemyState.h"
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
    this->crow = crow_;
    Vec2D playerDistance = crow_->getPlayerDistance();
    velocity = getVelocityTowardPosition(playerDistance, {1, 1}, SPEED);
}

void CrowGiftingPebbleState::update(Crow *crow) {
    this->crow = crow;
    Vec2D playerDistance = crow->getPlayerDistance();

    if (std::abs(playerDistance.x) <= STOP_DISTANCE && std::abs(playerDistance.y) <= STOP_DISTANCE) {
        crow->dropPebble();
        crow->setState(new CrowIdleState(crow));
        return;
    }

    velocity = getVelocityTowardPosition(playerDistance, velocity, SPEED);
    crow->pos = crow->pos - velocity;
}

CrowFindingEnemyToDistractState::CrowFindingEnemyToDistractState(Crow *crow_) : CrowState(crow_) {
    this->crow = crow_;
    enemy = *(Enemy::attackingEnemies.begin());

    Vec2D dist = crow_->pos - enemy->pos;
    velocity = getVelocityTowardPosition(dist, {1, 1}, SPEED);
}

void CrowFindingEnemyToDistractState::update(Crow *crow_) {
    this->crow = crow_;
    if (Enemy::attackingEnemies.find(enemy) == Enemy::attackingEnemies.end()) {
        crow_->setState(new CrowIdleState(crow_));
        return;
    }

    Vec2D dist = crow_->pos - enemy->pos;
    if (std::abs(dist.x) <= STOP_DISTANCE && std::abs(dist.y) <= STOP_DISTANCE) {
        crow_->setState(new CrowScaringEnemyState(crow_, enemy));
        return;
    }

    velocity = getVelocityTowardPosition(dist, velocity, SPEED);
    crow_->pos = crow_->pos - velocity;
}

CrowScaringEnemyState::CrowScaringEnemyState(Crow *crow_, Enemy *enemy_)
    : CrowState(crow) {
    this->crow = crow_;
    this->enemy = enemy_;

    if (Enemy::attackingEnemies.find(enemy_) == Enemy::attackingEnemies.end()) {
        crow_->setState(new CrowIdleState(crow_));
        return;
    }
    releaseDistance = enemy_->attackDistance + 500;

    Vec2D crowToPlayerDist = crow_->getPlayerDistance();
    Vec2D targetDist = {
        (crowToPlayerDist.x < 0 ? 1 : -1) * releaseDistance,
        (crowToPlayerDist.y < 0 ? 1 : -1) * releaseDistance
    };
    targetPos = crow_->pos + targetDist;

    velocity = getVelocityTowardPosition(crow_->pos - targetPos, velocity, SPEED);
    enemy_->setState(new EnemyFollowingCrowState(*enemy, crow_, targetPos));
}

void CrowScaringEnemyState::update(Crow *crow_) {
    velocity = getVelocityTowardPosition(crow_->pos - targetPos, velocity, SPEED);
    Vec2D dist = targetPos - crow_->pos;

    if (std::abs(dist.x) <= STOP_DIST && std::abs(dist.y) <= STOP_DIST) {
        crow_->setState(new CrowIdleState(crow_));
        return;
    }
    
    crow_->pos = crow_->pos - velocity;
}