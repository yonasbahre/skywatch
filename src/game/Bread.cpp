#include "Bread.h"
#include "ColliderTags.h"
#include <iostream>

Bread::Bread(
    EngineObject *parent, 
    Vec2D const &screenTransform_
) : EngineObject(parent), screenTransform(screenTransform_) {
    collider.tag = BREAD;
    collider.onCollisionStart = [this](Collision col) {
        if (col.other->tag == PLAYER) {
            onDestroy(this);
        }
    };
}

Bread::~Bread() {}

Renderer *Bread::getRenderer() {
    return &renderer;
}

void Bread::start() {}

void Bread::update() {}

Bread::BreadRenderer::BreadRenderer(Bread *bread) : Renderer(bread) {
    this->bread = bread;
    sprite.scaleDimensions(1.2);
    sprite.setIsCentered(true);
}

Bread::BreadRenderer::~BreadRenderer() {}

void Bread::BreadRenderer::render() {
    sprite.draw(globalPos + bread->screenTransform);
}