#pragma once
#include "EngineObject.h"
#include "Collider.h"
#include "Renderer.h"

class FinishFlag : public EngineObject {
    class FinishFlagRenderer : public Renderer {
        FinishFlag *flag = nullptr;
    public:
        Sprite sprite = Sprite(this->sdlRenderer, "assets/finish.png");
    
        FinishFlagRenderer(FinishFlag *flag);
        ~FinishFlagRenderer();
        void render();
    };

    FinishFlagRenderer renderer = FinishFlagRenderer(this);
    Collider collider = Collider(renderer.sprite);

public:
    FinishFlag(
        EngineObject *parent,
        Vec2D const &screenTransform_
    );
    ~FinishFlag();

    Vec2D const &screenTransform;

    Renderer *getRenderer() override;
    void start();
    void update();
};