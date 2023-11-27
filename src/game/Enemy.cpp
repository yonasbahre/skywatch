#include "Enemy.h"
#include "EnemyRenderer.h"

#include <iostream>

Enemy::Enemy(
    EngineObject *parent,
    Vec2D const &screenTransform_
) : EngineObject(parent), screenTransform(screenTransform_) {
    enemyRenderer = new EnemyRenderer(this);
    renderer = enemyRenderer;
    collider = new Collider(enemyRenderer->sprite);
}

Enemy::~Enemy() {
    delete collider;
    delete enemyRenderer;
}

void Enemy::start() {}

void Enemy::update() {}

EnemyRenderer::EnemyRenderer(Enemy *enemy) : Renderer(enemy) {
    this->enemy = enemy;
}

void EnemyRenderer::render() {
    sprite.draw(Vec2D(0, 300) + enemy->screenTransform);
}