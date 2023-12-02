#include "Enemy.h"
#include "EnemyRenderer.h"

const float Enemy::DAMAGE_DEALT = 10;

Enemy::Enemy(
    EngineObject *parent,
    Vec2D const &screenTransform_
) : EngineObject(parent), screenTransform(screenTransform_) {
    collider.tag = "ENEMY";
}

Enemy::~Enemy() {}

Renderer *Enemy::getRenderer() {
    return &renderer;
}

void Enemy::start() {}

void Enemy::update() {}

EnemyRenderer::EnemyRenderer(Enemy *enemy) : Renderer(enemy) {
    this->enemy = enemy;
    sprite.scaleDimensions(0.35);
}

EnemyRenderer::~EnemyRenderer() {}

void EnemyRenderer::render() {
    sprite.draw(Vec2D(0, 300) + enemy->screenTransform);
}