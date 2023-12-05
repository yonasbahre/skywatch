#pragma once
#include "Engine.h"
#include "EngineObject.h"
#include "Sprite.h"
#include "Collider.h"

class Crow : public EngineObject {
    class CrowRenderer : public Renderer {
        Crow *crow = nullptr;
    public:
        Sprite sprite = Sprite(this->sdlRenderer, "assets/crow.png");
    
        CrowRenderer(Crow *crow);
        ~CrowRenderer();
        void render();
    };

    const float SIGHTING_DISTANCE = 200;

    CrowRenderer renderer = CrowRenderer(this);
    Collider collider = Collider(renderer.sprite);

    // Determines the bounds of the sightCollider
    Sprite sightColliderSprite = Sprite(
        Engine::getEngine()->renderer, 
        "assets/1x1.png"
    );

    // This collider is used to determine whether a crow
    // is close enough to "see" the player
    Collider sightCollider = Collider(sightColliderSprite);

public:
    Crow(
        EngineObject *parent,
        Vec2D const &screenTransform_
    );

    ~Crow();

    Vec2D const &screenTransform;
    std::function<void(EngineObject*)> onDestroy;
    Vec2D pos = {0, 0};
    
    Renderer *getRenderer() override;
    void start();
    void update();
};