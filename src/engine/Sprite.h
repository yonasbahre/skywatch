#pragma once
#include <string>
#include <SDL2/SDL.h>
#include "Vec2D.h"

class Sprite {
    SDL_Renderer *sdlRenderer;
    SDL_Texture *sdlTexture;
    SDL_Rect sdlRect;

    std::string spritePath = "";
    bool isCentered = false;
    bool isVisible = true;

public:
    Sprite(SDL_Renderer *sdlRenderer, std::string spritePath);
    ~Sprite();

    void draw();
    void draw(Vec2D pos);

    void setPos(Vec2D pos);
    void setDimensions(Vec2D pos);
    void scaleDimensions(float scaleFactor);
    void setIsCentered(bool isCentered);
    void setIsVisible(bool isVisible);

    Vec2D getDimensions();
};