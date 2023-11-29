#include <iostream>
#include <algorithm>
#include "Constants.h"
#include "Engine.h"
#include "LevelDirectory.h"
#include "Player.h"
#include "Enemy.h"

Player::Player(
    EngineObject *parent,
    std::function<int(Vec2D)> getRoadSegmentOfPoint,
    std::function<void(int)> updateCurrRoadSegment
) : EngineObject(parent) {
    this->getRoadSegmentOfPoint = getRoadSegmentOfPoint;
    this->updateCurrRoadSegment = updateCurrRoadSegment;
    
    PlayerRenderer *playerRenderer = new PlayerRenderer(this);
    renderer = playerRenderer;
    renderer->pos = Vec2D(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    collider = new Collider(playerRenderer->sprite);
    collider->tag = "PLAYER";

    collider->onCollisionStart = [this](Collision col) {
        if (col.other->tag == "ENEMY") {
            decreaseHealth(Enemy::DAMAGE_DEALT);
        }
    };

    eventMgr = EventManager::getManager();
}

Player::~Player() {
    delete collider;
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
        getRoadSegmentOfPoint({corners[0], corners[1]}),
        getRoadSegmentOfPoint({corners[0], corners[3]}),
        getRoadSegmentOfPoint({corners[2], corners[1]}),
        getRoadSegmentOfPoint({corners[2], corners[3]})
    };
    
    int minIndex = *std::min_element(cornerIndices.begin(), cornerIndices.end());
    if (minIndex != -1) {
        updateCurrRoadSegment(minIndex);
        this->worldPos= worldPos;
    }
}

Vec2D Player::getWorldPos() {
    return worldPos;
}

void Player::decreaseHealth(float amount) {
    float prevHealth = health;
    health -= amount;

    if (health <= 0) {
        Engine::getEngine()->loadLevel(LEVEL_1);
    }
}

PlayerRenderer::PlayerRenderer(Player *object) : Renderer(object) {
    sprite.setIsCentered(true);
    sprite.scaleDimensions(0.25);
}

PlayerRenderer::~PlayerRenderer() {}

void PlayerRenderer::render() {
    sprite.draw(globalPos);
}