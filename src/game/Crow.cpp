#include "ColliderTags.h"
#include "Crow.h"
#include "CrowState.h"
#include "Utils.h"
#include "Enemy.h"
#include <iostream>

Crow::Crow(
    EngineObject *parent, 
    Vec2D const &screenTransform_,
    Player &player_,
    Vec2D startPos_,
    CrowField &crowField_,
    LevelUI &levelUI_,
    std::function<void()> increaseEnemyAttackRadiuses_,
    std::function<void(Vec2D)> spawnPebble_
) : EngineObject(parent), 
    screenTransform(screenTransform_), 
    player(player_), 
    startPos(startPos_),
    crowField(crowField_),
    ui(levelUI_),
    increaseEnemyAttackRadiuses(increaseEnemyAttackRadiuses_),
    spawnPebble(spawnPebble_)
{    
    pos = startPos;
    state = new CrowIdleState(this);
    
    collider.tag = CROW;
    collider.onCollisionStart = [this](Collision &col) {
        if (col.other->tag == PLAYER) {
            player.addToAdjacentCrows(this);
        } else if (col.other->tag == PLAYER_PROJECTILE) {
            crowField.addIncident(crowField.VERY_NEGATIVE_INTERACTION, pos);
            setAgitation(crowField.getAgitation(pos));
            ui.sendMsgToConsole("Uh oh, you just hit a crow!");
        }
    };

    collider.onCollisionExit = [this](Collision &col) {
        if (col.other->tag == PLAYER) {
            player.removeFromAdjacentCrows(this);
        }
    };

    sightColliderSprite.scaleDimensions(2 * SIGHTING_DISTANCE);
    sightColliderSprite.setIsCentered(true);

    sightCollider.tag = CROW_SIGHT;
    sightCollider.onCollisionStart = [this](Collision &col) {
        if (col.other->tag == PLAYER) {
            handleCrowSeeingPlayer();
        }
    };

    sightCollider.onCollisionExit = [this](Collision &col) {
        if (col.other->tag == PLAYER) {
            setState(new CrowIdleState(this));
        }
    };
}

Crow::~Crow() {
    player.removeFromAdjacentCrows(this);
    delete state;
}

Renderer *Crow::getRenderer() {
    return &renderer;
}

void Crow::start() {
    renderer.pos = this->pos + screenTransform;
    sightColliderSprite.setPos(renderer.globalPos);
}

void Crow::update() {
    state->update(this);

    renderer.pos = this->pos + screenTransform;
    sightColliderSprite.setPos(renderer.globalPos);
}

void Crow::handleCrowSeeingPlayer() {
    setAgitation(crowField.getAgitation(pos));
    
    if (agitation < -2000) {
        int probability = -agitation;
        bool willCaw = randInt(0, 10000) <= probability;
        if (willCaw) {
            caw();
        }
    }
    else if (agitation > 1000) {
        bool willDropPebble = randInt(0, 1);
        if (willDropPebble) {
            setState(new CrowGiftingPebbleState(this));
        }
    }
    else if (agitation > 6000 && !Enemy::attackingEnemies.empty()) {
        bool willScareEnemy = randInt(0, 1);
        if (willScareEnemy) {
            setState(new CrowFindingEnemyToDistractState(this));
            ui.sendMsgToConsole("A crow is scaring an enemy away!");
        }
    }
}

void Crow::feed() {
    crowField.addIncident(crowField.POSITIVE_INTERACTION, pos);
    setAgitation(crowField.getAgitation(pos));
}

void Crow::pluck() {
    crowField.addIncident(crowField.NEGATIVE_INTERACTION, pos);
    setAgitation(crowField.getAgitation(pos));
}

void Crow::caw() {
    increaseEnemyAttackRadiuses();
    ui.sendMsgToConsole("A crow cawed! Enemies might have heard...");
    canTakeAction = false;
}

void Crow::dropPebble() {
    spawnPebble(pos);
    ui.sendMsgToConsole("A crow gifted a pebble to you!");
    canTakeAction = false;
}

void Crow::setState(CrowState *newState) {
    CrowState *oldState = state;
    state = newState;
    delete oldState;
}

float Crow::getAgitation() {
    return this->agitation;
}

void Crow::setAgitation(float agitation) {
    this->agitation = agitation;
    canTakeAction = true;
}

Vec2D Crow::getPlayerDistance() {
    return pos - player.getAdjustedPos();
}

Crow::CrowRenderer::CrowRenderer(Crow *crow) : Renderer(crow) {
    this->crow = crow;
    sprite.scaleDimensions(0.9);
    sprite.setIsCentered(true);
}

Crow::CrowRenderer::~CrowRenderer() {}

void Crow::CrowRenderer::render() {
    sprite.draw(globalPos);
}