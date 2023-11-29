#pragma once
#include "EngineObject.h"
#include "Renderer.h"
#include "Sprite.h"
#include "EnemyRenderer.h"
#include "Collider.h"

class Enemy : public EngineObject {
    EnemyRenderer renderer = EnemyRenderer(this);
    Collider collider = Collider(renderer.sprite);

public:
    static const float DAMAGE_DEALT;

    Enemy(
        EngineObject *parent,
        Vec2D const &screenTransform_
    );
    ~Enemy();

    Vec2D const &screenTransform;

    Renderer *getRenderer() override;
    void start();
    void update();
};
