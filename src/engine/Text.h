#pragma once
#include <string>
#include <SDL2/SDL_ttf.h>
#include "Vec2D.h"

class Text {
    SDL_Renderer *sdlRenderer;
    TTF_Font *ttfFont;
    SDL_Surface *sdlSurface;
    SDL_Texture *sdlTexture;
    SDL_Rect sdlRect;

    SDL_Color color = {255, 255, 255};
    std::string textContent = "Sample Text";
    std::string fontPath = "";
    int ptSize = 12;
    bool isCentered = false;
    bool isVisible = true;

    void updateSurfaceAndTexture();

public:
    Text(
        SDL_Renderer *sdlRenderer, 
        std::string fontPath,
        int ptSize = 12
    );
    ~Text();
    
    void draw();
    void draw(Vec2D pos);

    void setColor(SDL_Color color);
    void setPos(Vec2D pos);
    void setText(std::string newText);
    void setPtSize(int ptSize);
    void setIsCentered(bool isCentered);
    void setIsVisible(bool isVisible);

    Vec2D getDimensions();
    bool getIsVisible();
};