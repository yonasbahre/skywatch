#include "Projectile.h"
#include "ColliderTags.h"

Projectile::Projectile(
    EngineObject *parent,
    Vec2D const &screenTransform_,
    Vec2D startPos,
    Direction direction_
) : EngineObject(parent), 
    screenTransform(screenTransform_), 
    pos(startPos), 
    direction(direction_) 
{
    collider.tag = PLAYER_PROJECTILE;
    collider.onCollisionStart = [this](Collision col) {
        if (col.other->tag == ENEMY) {
            deleteOnNextFrame = true;
        }
    };

    switch (direction) {
        case UP:
            velocity = {0, -SPEED};
            break;
        case DOWN:
            velocity = {0, SPEED};
            break;
        case LEFT:
            velocity = {-SPEED, 0};
            break;
        case RIGHT:
            velocity = {SPEED, 0};
            break;
    }
}

Projectile::~Projectile() {
    if (isDeleted != nullptr) {
        *isDeleted = true;
    }
    if (selfDestructThread) {
        SDL_DetachThread(selfDestructThread);
        selfDestructThread = nullptr;
    }
}

Renderer *Projectile::getRenderer() {
    return &renderer;
}

void Projectile::start() {
    selfDestructThread = SDL_CreateThread(destroyAfterTimer, nullptr, this);
}

void Projectile::update() {
    if (deleteOnNextFrame) {
        delete this;
        return;
    }

    pos = pos + velocity;
    renderer.pos = pos;
}

int Projectile::destroyAfterTimer(void *thisProjectile) {
    bool isDeleted = false;
    Projectile *projectile = static_cast<Projectile*>(thisProjectile);
    projectile->isDeleted = &isDeleted;

    SDL_Delay(projectile->TIME_TO_DELETE_MILLISECONDS);
    if (!isDeleted) {
        projectile->deleteOnNextFrame = true;
        projectile->isDeleted = nullptr;
    }

    return 0;
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