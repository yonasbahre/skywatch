#include "ColliderTags.h"
#include "Enemy.h"
#include "EnemyRenderer.h"
#include "EnemyState.h"
#include <iostream>

const float Enemy::DAMAGE_DEALT = 10;

Enemy::Enemy(
    EngineObject *parent,
    Vec2D const &screenTransform_,
    Vec2D startPos_
) : EngineObject(parent), screenTransform(screenTransform_), startPos(startPos_) {
    collider.tag = ENEMY;
    collider.onCollisionStart = [this](Collision col) {
        if (col.other->tag == PLAYER_PROJECTILE) {
            onDestroy(this);
        }
    };

    pos = startPos;
    state = new EnemyIdleState(*this);
}

Enemy::~Enemy() {
    delete state;
}

Renderer *Enemy::getRenderer() {
    return &renderer;
}

void Enemy::start() {
    renderer.pos = this->pos;
    renderer.sprite.setPos(renderer.pos);
}

void Enemy::update() {
    state->update();
    renderer.pos = this->pos;
}

EnemyRenderer::EnemyRenderer(Enemy *enemy) : Renderer(enemy) {
    this->enemy = enemy;
    sprite.setIsCentered(true);
    sprite.scaleDimensions(0.35);
}

EnemyRenderer::~EnemyRenderer() {}

void EnemyRenderer::render() {
    sprite.draw(globalPos + enemy->screenTransform);
}