#pragma once
#include "EngineObject.h"
#include "EventManager.h"
#include "Text.h"

class FinishScreen : public EngineObject {
    class FinishScreenRenderer : public Renderer {
    public:
        Text youMadeIt = Text(
            this->sdlRenderer, 
            "assets/Imperator Bold.ttf", 
            144
        );

        Text pressToReturn = Text(
            this->sdlRenderer,
            "assets/Imperator.ttf",
            72
        );

        FinishScreenRenderer(FinishScreen *object);
        ~FinishScreenRenderer();
        void render();
    };

    FinishScreenRenderer renderer = FinishScreenRenderer(this);
    EventManager *eventMgr = nullptr;

public:
    FinishScreen();
    ~FinishScreen();

    Renderer *getRenderer() override;
    void start();
    void update();
};