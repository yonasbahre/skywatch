#include "ColliderTags.h"
#include "Crow.h"
#include <iostream>

Crow::Crow(
    EngineObject *parent, 
    Vec2D const &screenTransform_
) : EngineObject(parent), screenTransform(screenTransform_) {    
    collider.tag = CROW;
    collider.onCollisionStart = [](Collision &col) {
        if (col.other->tag == PLAYER) {
            std::cout << "You just hit a crow\n";
        }
    };

    collider.onCollisionExit = [](Collision &col) {
        if (col.other->tag == PLAYER) {
            std::cout << "Collision exited\n";
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

Crow::~Crow() {}

Renderer *Crow::getRenderer() {
    return &renderer;
}

void Crow::start() {}

void Crow::update() {
    renderer.pos = this->pos + screenTransform;
    sightColliderSprite.setPos(renderer.globalPos);
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