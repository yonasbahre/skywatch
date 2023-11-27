#pragma once
#include "EngineObject.h"
#include "Renderer.h"
#include "Sprite.h"
#include "EnemyRenderer.h"
#include "Collider.h"

class Enemy : public EngineObject {
    EnemyRenderer *enemyRenderer = nullptr;
    Collider *collider = nullptr;

public:
    Enemy(
        EngineObject *parent,
        Vec2D const &screenTransform_
    );
    ~Enemy();

    Vec2D const &screenTransform;

    void start();
    void update();
};
