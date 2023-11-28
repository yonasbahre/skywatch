#pragma once
#include "Vec2D.h"

class EngineObject;
struct SDL_Renderer;

class Renderer {
protected:
    EngineObject *object;
    SDL_Renderer *sdlRenderer;
public:
    Renderer(EngineObject *object);
    // ~Renderer();

    Vec2D pos = {0, 0};
    Vec2D globalPos = {0, 0};

    void updateGlobalPosAndRender();
    virtual void render() = 0;
};