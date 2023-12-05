#include "ColliderTags.h"
#include "Enemy.h"
#include "EnemyRenderer.h"

const float Enemy::DAMAGE_DEALT = 10;

Enemy::Enemy(
    EngineObject *parent,
    Vec2D const &screenTransform_
) : EngineObject(parent), screenTransform(screenTransform_) {
    collider.tag = ENEMY;
}

Enemy::~Enemy() {}

Renderer *Enemy::getRenderer() {
    return &renderer;
}

void Enemy::start() {}

void Enemy::update() {
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