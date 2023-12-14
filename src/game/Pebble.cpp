#include "Pebble.h"
#include "ColliderTags.h"

Pebble::Pebble(
    EngineObject *parent,
    Vec2D const &screenTransform_
) : EngineObject(parent), screenTransform(screenTransform_) {
    collider.tag = PEBBLE;
    collider.onCollisionStart = [this](Collision col) {
        if (col.other->tag == PLAYER) {
            onDestroy(this);
        }
    };
}

Pebble::~Pebble() {}

Renderer *Pebble::getRenderer() {
    return &renderer;
}

void Pebble::start() {}

void Pebble::update() {}

Pebble::PebbleRenderer::PebbleRenderer(Pebble *pebble) : Renderer(pebble) {
    this->pebble = pebble;
    sprite.scaleDimensions(0.02);
    sprite.setIsCentered(true);
}

Pebble::PebbleRenderer::~PebbleRenderer() {}

void Pebble::PebbleRenderer::render() {
    sprite.draw(globalPos + pebble->screenTransform);
}


