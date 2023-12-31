#pragma once
#include "Enemy.h"
#include "Direction.h"

class Crow;

class EnemyState {
public:
    Enemy &enemy;

    EnemyState(Enemy &enemy_);
    virtual void update() = 0;
};

class EnemyIdleState : public EnemyState {
    const float MAX_IDLE_DIST = 300;
    const float IDLE_SPEED = 0.7;

    Vec2D velocity = {0, 0};
public:
    EnemyIdleState(Enemy &enemy_);
    void update();
};

class EnemyAttackState : public EnemyState {
    const float ATTACK_SPEED = 1.5;
    Vec2D velocity = {0, 0};

public:
    EnemyAttackState(Enemy &enemy_);
    void update();
};

class EnemyCooldownState : public EnemyState {
    const int COOLDOWN_MILLISECONDS = 6000;
    long long endCooldownTime;

public:
    EnemyCooldownState(Enemy &enemy_);
    void update();
};

class EnemyFollowingCrowState : public EnemyState {
    const float SPEED = 2;
    const float STOP_DIST = 20;
    Vec2D velocity = {0, 0};
    Vec2D targetPos = {0, 0};
    bool useTargetPos = false;
    Crow *crow = nullptr;

public:
    EnemyFollowingCrowState(Enemy &enemy_, Crow *crow_);
    EnemyFollowingCrowState(Enemy &enemy_, Crow *crow_, Vec2D targetPos);
    void update();
};