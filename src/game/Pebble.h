#pragma once
#include "EngineObject.h"
#include "Sprite.h"
#include "Collider.h"

class Pebble : public EngineObject {
    class PebbleRenderer : public Renderer {
        Pebble *pebble = nullptr;
    public:
        Sprite sprite = Sprite(this->sdlRenderer, "assets/pebble.png");

        PebbleRenderer(Pebble *pebble);
        ~PebbleRenderer();
        void render();
    };

    PebbleRenderer renderer = PebbleRenderer(this);
    Collider collider = Collider(renderer.sprite);

public:
    Pebble(
        EngineObject *parent,
        Vec2D const &screenTransform_
    );
    ~Pebble();

    Vec2D const &screenTransform;
    std::function<void(EngineObject*)> onDestroy;

    Renderer *getRenderer() override;
    void start();
    void update();
};