#include "ColliderTags.h"
#include "Crow.h"
#include <iostream>

Crow::Crow(
    EngineObject *parent, 
    Vec2D const &screenTransform_,
    Player &player_
) : EngineObject(parent), screenTransform(screenTransform_), player(player_) {    
    collider.tag = CROW;
    collider.onCollisionStart = [this](Collision &col) {
        if (col.other->tag == PLAYER) {
            std::cout << "You just hit a crow\n";
            player.addToAdjacentCrows(this);
        } else if (col.other->tag == PLAYER_PROJECTILE) {
            std::cout << "Uh oh, you just hit a crow!\n";
            // TODO: Respond to being hit (crowfield)
        }
    };

    collider.onCollisionExit = [this](Collision &col) {
        if (col.other->tag == PLAYER) {
            std::cout << "Collision with crow exited\n";
            player.removeFromAdjacentCrows(this);
        }
    };

    sightColliderSprite.scaleDimensions(2 * SIGHTING_DISTANCE);
    sightColliderSprite.setIsCentered(true);

    sightCollider.tag = CROW_SIGHT;
    sightCollider.onCollisionStart = [](Collision &col) {
        if (col.other->tag == PLAYER) {
            std::cout << "The crow can see you\n";
        }
    };

    sightCollider.onCollisionExit = [this](Collision &col) {
        if (col.other->tag == PLAYER) {
            std::cout << "The crow can't see you anymore\n";
        }
    };
}

Crow::~Crow() {
    player.removeFromAdjacentCrows(this);
}

Renderer *Crow::getRenderer() {
    return &renderer;
}

void Crow::start() {}

void Crow::update() {
    renderer.pos = this->pos + screenTransform;
    sightColliderSprite.setPos(renderer.globalPos);
}

void Crow::feed() {
    // TODO: implement
    std::cout << "You fed the crow!\n";
}

void Crow::pluck() {
    // TODO: implement
    std::cout << "You just plucked the crow! :(\n";
}

Crow::CrowRenderer::CrowRenderer(Crow *crow) : Renderer(crow) {
    this->crow = crow;
    sprite.scaleDimensions(0.5);
    sprite.setIsCentered(true);
}

Crow::CrowRenderer::~CrowRenderer() {}

void Crow::CrowRenderer::render() {
    sprite.draw(globalPos);
}