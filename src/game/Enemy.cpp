#include "Enemy.h"
#include "EnemyRenderer.h"

#include <iostream>

const float Enemy::DAMAGE_DEALT = 100;

Enemy::Enemy(
    EngineObject *parent,
    Vec2D const &screenTransform_
) : EngineObject(parent), screenTransform(screenTransform_) {
    enemyRenderer = new EnemyRenderer(this);
    renderer = enemyRenderer;
    collider = new Collider(enemyRenderer->sprite);
    collider->tag = "ENEMY";
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

EnemyRenderer::~EnemyRenderer() {}

void EnemyRenderer::render() {
    sprite.draw(Vec2D(0, 300) + enemy->screenTransform);
}