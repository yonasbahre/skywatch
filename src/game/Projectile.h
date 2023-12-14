#pragma once 
#include "EngineObject.h"
#include "Sprite.h"
#include "Collider.h"

// Do not allocate on stack
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
    
    const int TIME_TO_DELETE_MILLISECONDS = 2000;
    bool deleteOnNextFrame = false; 
    SDL_Thread *selfDestructThread = nullptr;
    bool *isDeleted = nullptr;  // for ending thread
    static int destroyAfterTimer(void *thisProjectile);

public:
    Projectile(
        EngineObject *parent,
        Vec2D const &screenTransform_
    );
    ~Projectile();

    Vec2D pos = {0, 0};

    Vec2D const &screenTransform;
    std::function<void(EngineObject*)> onDestroy;

    Renderer *getRenderer() override;
    void start();
    void update();
};