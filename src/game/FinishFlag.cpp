#include "FinishFlag.h"
#include "ColliderTags.h"
#include "Engine.h"
#include "LevelDirectory.h"

FinishFlag::FinishFlag(
    EngineObject *parent,
    Vec2D const &screenTransform_
) : EngineObject(parent), screenTransform(screenTransform_) {
    collider.tag = FINISH;
    collider.onCollisionStart = [](Collision col) {
        if (col.other->tag == PLAYER) {
            Engine::getEngine()->loadLevel(FINISH_SCREEN);
        }
    };
}

FinishFlag::~FinishFlag() {}

Renderer *FinishFlag::getRenderer() {
    return &renderer;
}

void FinishFlag::start() {}

void FinishFlag::update() {}

FinishFlag::FinishFlagRenderer::FinishFlagRenderer(FinishFlag *flag)
    : Renderer(flag) {
    this->flag = flag;
    sprite.setIsCentered(true);
}

FinishFlag::FinishFlagRenderer::~FinishFlagRenderer() {}

void FinishFlag::FinishFlagRenderer::render() {
    sprite.draw(globalPos + flag->screenTransform);
}