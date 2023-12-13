#pragma once
#include "EngineObject.h"
#include "Sprite.h"
#include "Collider.h"

class Bread : public EngineObject {
    class BreadRenderer : public Renderer {
        Bread *bread = nullptr;
    public:
        Sprite sprite = Sprite(this->sdlRenderer, "assets/bread.png");

        BreadRenderer(Bread *bread);
        ~BreadRenderer();
        void render();
    };

    BreadRenderer renderer = BreadRenderer(this);
    Collider collider = Collider(renderer.sprite);

public:
    Bread(
        EngineObject *parent,
        Vec2D const &screenTransform_
    );
    
    ~Bread();

    Vec2D const &screenTransform;
    std::function<void(EngineObject*)> onDestroy;

    Renderer *getRenderer() override;
    void start();
    void update();
};