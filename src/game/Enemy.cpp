#include "ColliderTags.h"
#include "Enemy.h"
#include "EnemyRenderer.h"
#include "EnemyState.h"
#include <iostream>

const float Enemy::DAMAGE_DEALT = 10;

Enemy::Enemy(
    EngineObject *parent,
    Vec2D const &screenTransform_,
    Vec2D startPos_,
    Player &player_
) : EngineObject(parent), 
    screenTransform(screenTransform_), 
    startPos(startPos_),
    player(player_)
{
    collider.tag = ENEMY;
    collider.onCollisionStart = [this](Collision col) {
        if (col.other->tag == PLAYER_PROJECTILE) {
            onDestroy(this);
        }
        if (col.other->tag == PLAYER) {
            handlePlayerCollision();
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

void Enemy::setState(EnemyState *newState) {
    EnemyState *oldState = state;
    state = newState;
    delete oldState;
}

Vec2D Enemy::getPlayerDistance() {
    return pos - (player.getWorldPos() * Vec2D(-1, -1));
}

void Enemy::handlePlayerCollision() {
    setState(new EnemyCooldownState(*this));
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