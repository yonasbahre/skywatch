#pragma once
#include "Enemy.h"
#include "Direction.h"

class EnemyState {
public:
    Enemy &enemy;

    EnemyState(Enemy &enemy_);
    virtual void update() = 0;
};

class EnemyIdleState : public EnemyState {
    const float MAX_IDLE_DIST = 300;
    const float IDLE_SPEED = 0.02;

    Direction direction;
    Vec2D velocity = {0, 0};

    Vec2D getVelocityFromDirection(Direction direction);

public:
    EnemyIdleState(Enemy &enemy_);
    void update();
};