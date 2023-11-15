#pragma once

class EngineObject;
struct SDL_Renderer;

class Renderer {
protected:
    EngineObject *object;
    SDL_Renderer *sdlRenderer;
public:
    Renderer(EngineObject *object);
    float x = 0;
    float y = 0;
    float relativeX = 0;
    float relativeY = 0;
    virtual void render() = 0;
};