#pragma once 
#include "EngineObject.h"
#include "Sprite.h"
#include "Collider.h"

class Projectile : public EngineObject {
    class ProjectileRenderer : public Renderer {
        Projectile *projectile = nullptr;
    public:
        Sprite sprite = Sprite(this->sdlRenderer, "assets/pebble.png");

        ProjectileRenderer(Projectile *projectile);
        ~ProjectileRenderer();
        void render();
    };

    ProjectileRenderer renderer = ProjectileRenderer(this);
    Collider collider = Collider(renderer.sprite);

    const float SPEED = 5.0f;
    const long TIME_TO_DELETE_MILLISECONDS = 2000;
    bool deleteOnNextFrame = false; 
    bool *isDeleted = nullptr;  // for ending threads

public:
    Projectile(
        EngineObject *parent,
        Vec2D const &screenTransform_
    );
    ~Projectile();

    Vec2D const &screenTransform;
    std::function<void(EngineObject*)> onDestroy;

    Renderer *getRenderer() override;
    void start();
    void update();
};