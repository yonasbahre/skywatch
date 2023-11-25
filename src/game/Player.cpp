#include <iostream>
#include <algorithm>
#include "Constants.h"
#include "Player.h"

Player::Player(
    EngineObject *parent,
    std::function<int(Vec2D)> getRoadIndexOfPoint,
    std::function<void(int)> updateRoadIndex
) : EngineObject(parent) {
    this->getRoadIndexOfPoint = getRoadIndexOfPoint;
    this->updateRoadIndex = updateRoadIndex;
    
    renderer = new PlayerRenderer(this);
    renderer->pos = Vec2D(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    eventMgr = EventManager::getManager();
}

void Player::start() {}

void Player::update() {
    float scaleFactor = eventMgr->keyStates[SDL_SCANCODE_LSHIFT] ? sprintScale : 1;

    if (eventMgr->keyStates[SDL_SCANCODE_W] || eventMgr->keyStates[SDL_SCANCODE_UP]) {
        setWorldPos(worldPos + Vec2D(0, scaleFactor * speed));
    } else if (eventMgr->keyStates[SDL_SCANCODE_S] || eventMgr->keyStates[SDL_SCANCODE_DOWN]) {
        setWorldPos(worldPos + Vec2D(0, scaleFactor * -speed));
    } else if (eventMgr->keyStates[SDL_SCANCODE_A] || eventMgr->keyStates[SDL_SCANCODE_LEFT]) {
        setWorldPos(worldPos + Vec2D(scaleFactor * speed, 0));
    } else if (eventMgr->keyStates[SDL_SCANCODE_D] || eventMgr->keyStates[SDL_SCANCODE_RIGHT]) {
        setWorldPos(worldPos + Vec2D(scaleFactor * -speed, 0));
    }
}

void Player::setWorldPos(Vec2D worldPos) {
    PlayerRenderer *renderer_ = dynamic_cast<PlayerRenderer*>(renderer);
    std::vector<float> corners = renderer_->sprite.getCorners();
    corners[0] -= worldPos.x + SCREEN_WIDTH / 2;
    corners[1] -= worldPos.y + SCREEN_HEIGHT / 2;
    corners[2] -= worldPos.x + SCREEN_WIDTH / 2;
    corners[3] -= worldPos.y + SCREEN_HEIGHT / 2;
    
    std::vector<int> cornerIndices = {
        getRoadIndexOfPoint({corners[0], corners[1]}),
        getRoadIndexOfPoint({corners[0], corners[3]}),
        getRoadIndexOfPoint({corners[2], corners[1]}),
        getRoadIndexOfPoint({corners[2], corners[3]})
    };
    
    int minIndex = *std::min_element(cornerIndices.begin(), cornerIndices.end());
    if (minIndex != -1) {
        updateRoadIndex(minIndex);
        this->worldPos= worldPos;
    }
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