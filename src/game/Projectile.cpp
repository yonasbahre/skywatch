#include "Projectile.h"
#include "ColliderTags.h"

Projectile::Projectile(
    EngineObject *parent,
    Vec2D const &screenTransform_
) : EngineObject(parent), screenTransform(screenTransform_) {
    collider.tag = PLAYER_PROJECTILE;
}

Projectile::~Projectile() {}

Renderer *Projectile::getRenderer() {
    return &renderer;
}

void Projectile::start() {}

void Projectile::update() {
    if (deleteOnNextFrame) {
        delete this;
        return;
    }
}

Projectile::ProjectileRenderer::ProjectileRenderer(Projectile *projectile)
    : Renderer(projectile) {
    this->projectile = projectile;
    sprite.scaleDimensions(0.02);
    sprite.setIsCentered(true);
}

Projectile::ProjectileRenderer::~ProjectileRenderer() {}

void Projectile::ProjectileRenderer::render() {
    sprite.draw(globalPos + projectile->screenTransform);
}