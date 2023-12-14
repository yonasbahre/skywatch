#include <iostream>
#include <algorithm>
#include "Constants.h"
#include "Engine.h"
#include "LevelDirectory.h"
#include "ColliderTags.h"
#include "Player.h"
#include "Enemy.h"
#include "SDLUtils.h"

Player::Player(
    EngineObject *parent,
    LevelUI &ui_,
    std::function<int(Vec2D)> getRoadSegmentOfPoint,
    std::function<void(int)> updateCurrRoadSegment
) : EngineObject(parent), ui(ui_) {
    this->getRoadSegmentOfPoint = getRoadSegmentOfPoint;
    this->updateCurrRoadSegment = updateCurrRoadSegment;
    
    renderer.pos = Vec2D(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    collider.tag = PLAYER;

    collider.onCollisionStart = [this](Collision col) {
        if (col.other->tag == ENEMY) {
            decreaseHealth(Enemy::DAMAGE_DEALT);
        } else if (col.other->tag == BREAD) {
            pickupBread();
        } else if (col.other->tag == PEBBLE) {
            pickupAmmo();
            ui.sendMsgToConsole("You picked up some pebbles!");
        } else if (col.other->tag == CROW) {
            // TODO: for testing, delete later
            ui.sendMsgToConsole("You hit a crow!");
        }
    };

    eventMgr = EventManager::getManager();
}

Player::~Player() {}

Renderer *Player::getRenderer() {
    return &renderer;
}

void Player::start() {
    health = MAX_HEALTH;
    ui.updateHealthUI(health);
    ui.updateBreadCountUI(breadCount);
    ui.updateAmmoCountUI(ammoCount);
}

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
    std::vector<float> corners = renderer.sprite.getCorners();
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
    ui.updateHealthUI(health);
    ui.sendMsgToConsole("You got hit by an enemy!");

    if (health <= 0) {
        Engine::getEngine()->loadLevel(LEVEL_1);
    }
}

void Player::pickupBread() {
    breadCount += 4;
    ui.updateBreadCountUI(breadCount);
    ui.sendMsgToConsole("You picked up some bread!");
}

void Player::pickupAmmo() {
    ammoCount += 2;
    ui.updateAmmoCountUI(ammoCount);
}

Player::PlayerRenderer::PlayerRenderer(Player *object) : Renderer(object) {
    sprite.setIsCentered(true);
    sprite.scaleDimensions(0.25);
}

Player::PlayerRenderer::~PlayerRenderer() {}

void Player::PlayerRenderer::render() {
    setSDLDrawColor(sdlRenderer, {255, 0, 0});
    SDL_Rect colliderRect = {           // For debugging only, delete when done
        (int) sprite.getCorners()[0],
        (int) sprite.getCorners()[1],
        (int) sprite.getDimensions().x,
        (int) sprite.getDimensions().y    
    };
    SDL_RenderDrawRect(sdlRenderer, &colliderRect);
    sprite.draw(globalPos);
}