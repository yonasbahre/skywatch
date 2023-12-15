#pragma once
#include "EngineObject.h"
#include "Renderer.h"
#include "Sprite.h"
#include "EnemyRenderer.h"
#include "Collider.h"
#include "Player.h"

class EnemyState;

class Enemy : public EngineObject {
    EnemyRenderer renderer = EnemyRenderer(this);
    Collider collider = Collider(renderer.sprite);
    Player &player;

    EnemyState *state;
    void handlePlayerCollision();

public:
    static const float DAMAGE_DEALT;
    const float INITIAL_ATTACK_DISTANCE = 400;
    const float ATTACK_DISTANCE_INCREASE = 200;
    float attackDistance = INITIAL_ATTACK_DISTANCE;

    Enemy(
        EngineObject *parent,
        Vec2D const &screenTransform_,
        Vec2D startPos_,
        Player &player_
    );
    ~Enemy();

    Vec2D const &screenTransform;
    std::function<void(EngineObject*)> onDestroy;
    const Vec2D startPos;
    Vec2D pos = {0, 0};

    Renderer *getRenderer() override;
    void start();
    void update();

    void setState(EnemyState *newState);
    Vec2D getPlayerDistance();
    void increaseAttackDistance();
};
