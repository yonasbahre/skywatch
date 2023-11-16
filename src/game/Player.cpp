#include <iostream>
#include "Constants.h"
#include "Player.h"

Player::Player(EngineObject *parent) : EngineObject(parent) {
    renderer = new PlayerRenderer(this);
    renderer->pos = Vec2D(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    eventMgr = EventManager::getManager();
}

void Player::start() {}

void Player::update() {
    if (eventMgr->keyStates[SDL_SCANCODE_W]) {
        setWorldPos(worldPos + Vec2D(0, -speed));
    }
    if (eventMgr->keyStates[SDL_SCANCODE_S]) {
        setWorldPos(worldPos + Vec2D(0, speed));
    }
    if (eventMgr->keyStates[SDL_SCANCODE_A]) {
        setWorldPos(worldPos + Vec2D(-speed, 0));
    }
    if (eventMgr->keyStates[SDL_SCANCODE_D]) {
        setWorldPos(worldPos + Vec2D(speed, 0));
    }
}

void Player::setWorldPos(Vec2D worldPos) {
    this->worldPos = worldPos;
}

Vec2D Player::getWorldPos() {
    return worldPos;
}

PlayerRenderer::PlayerRenderer(Player *object) : Renderer(object) {
    sprite.setIsCentered(true);
    sprite.scaleDimensions(0.25);
}

void PlayerRenderer::render() {
    sprite.draw(globalPos);
}