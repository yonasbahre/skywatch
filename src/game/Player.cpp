#include <iostream>
#include <algorithm>
#include "Engine.h"
#include "LevelDirectory.h"
#include "ColliderTags.h"
#include "Player.h"
#include "Enemy.h"
#include "Crow.h"
#include "SDLUtils.h"

Player::Player(
    EngineObject *parent,
    LevelUI &ui_,
    std::function<int(Vec2D)> getRoadSegmentOfPoint,
    std::function<void(int)> updateCurrRoadSegment,
    std::function<void(Direction)> fireProjectile
) : EngineObject(parent), ui(ui_) {
    this->getRoadSegmentOfPoint = getRoadSegmentOfPoint;
    this->updateCurrRoadSegment = updateCurrRoadSegment;
    this->fireProjectile = fireProjectile;
    
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
    ui.updateStaminaUI(stamina);
    ui.updateBreadCountUI(breadCount);
    ui.updateAmmoCountUI(ammoCount);
}

void Player::update() {
    bool isSprinting = 
        (eventMgr->keyStates[SDL_SCANCODE_LSHIFT] || eventMgr->keyStates[SDL_SCANCODE_RSHIFT]) && 
        stamina > 0.0f;
    float scaleFactor = isSprinting ? sprintScale : 1;

    if (eventMgr->keyStates[SDL_SCANCODE_W] || eventMgr->keyStates[SDL_SCANCODE_UP]) {
        setWorldPos(worldPos + Vec2D(0, scaleFactor * speed));
        lastDirection = UP;
        if (isSprinting) {
            decreaseStamina();
        }
    } else if (eventMgr->keyStates[SDL_SCANCODE_S] || eventMgr->keyStates[SDL_SCANCODE_DOWN]) {
        setWorldPos(worldPos + Vec2D(0, scaleFactor * -speed));
        lastDirection = DOWN;
        if (isSprinting) {
            decreaseStamina();
        }
    } else if (eventMgr->keyStates[SDL_SCANCODE_A] || eventMgr->keyStates[SDL_SCANCODE_LEFT]) {
        setWorldPos(worldPos + Vec2D(scaleFactor * speed, 0));
        lastDirection = LEFT;
        if (isSprinting) {
            decreaseStamina();
        }
    } else if (eventMgr->keyStates[SDL_SCANCODE_D] || eventMgr->keyStates[SDL_SCANCODE_RIGHT]) {
        setWorldPos(worldPos + Vec2D(scaleFactor * -speed, 0));
        lastDirection = RIGHT;
        if (isSprinting) {
            decreaseStamina();
        }
    }

    if (eventMgr->keyStates[SDL_SCANCODE_SPACE]) {
        if (!isSpacebarDown && ammoCount > 0) {
            fireProjectile(lastDirection);
            ammoCount--;
            ui.updateAmmoCountUI(ammoCount);
            isSpacebarDown = true;
        }
    } else {
        isSpacebarDown = false;
    }

    if (eventMgr->keyStates[SDL_SCANCODE_E]) {
        if (!isEKeyDown && breadCount > 0) {
            eatBread();
            isEKeyDown = true;
        }
    } else {
        isEKeyDown = false;
    }

    if (eventMgr->keyStates[SDL_SCANCODE_F]) {
        if (!isFKeyDown && breadCount > 0) {
            for (Crow *crow : adjacentCrows) {
                crow->feed();
            }
            breadCount--;
            ui.updateBreadCountUI(breadCount);
            ui.sendMsgToConsole("You just fed a crow!");
            isFKeyDown = true;
        }
    } else {
        isFKeyDown = false;
    }

    if (eventMgr->keyStates[SDL_SCANCODE_Q]) {
        if (!isQKeyDown) {
            for (Crow *crow : adjacentCrows) {
                crow->pluck();
            }
            ammoCount += 5;
            ui.updateAmmoCountUI(ammoCount);
            ui.sendMsgToConsole("You just plucked a crow's feathers! Arrows created.");
            isQKeyDown = true;
        }
    } else {
        isQKeyDown = false;
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

Vec2D Player::getAdjustedPos() {
    return worldPos * Vec2D(-1, -1);
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

void Player::addToAdjacentCrows(Crow *crow) {
    adjacentCrows.insert(crow);
}

void Player::removeFromAdjacentCrows(Crow *crow) {
    adjacentCrows.erase(crow);
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

void Player::decreaseStamina() {
    int oldRoundedStamina = (int) stamina;
    stamina -= STAMINA_DECREASE;
    int newRoundedStamina = (int) stamina;

    if (newRoundedStamina != oldRoundedStamina) {
        ui.updateStaminaUI(stamina);
    }
}

void Player::eatBread() {
    stamina += STAMINA_INCREASE;
    breadCount--;
    ui.updateStaminaUI(stamina);
    ui.updateBreadCountUI(breadCount);
    ui.sendMsgToConsole("You ate some bread!");
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