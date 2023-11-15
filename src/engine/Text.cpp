#include <iostream>
#include <stdexcept>
#include "Engine.h"
#include "Text.h"

Text::Text(SDL_Renderer *_sdlRenderer, std::string fontPath, int ptSize) {
    this->sdlRenderer = _sdlRenderer;
    this->fontPath = fontPath;
    this->ptSize = ptSize;
    ttfFont = TTF_OpenFont(fontPath.c_str(), ptSize);
    if (!ttfFont) {
        throw std::runtime_error("Failed to load font");
    }

    sdlSurface = TTF_RenderText_Blended(ttfFont, textContent.c_str(), color);
    sdlTexture = SDL_CreateTextureFromSurface(sdlRenderer, sdlSurface);
    sdlRect.w = sdlSurface->w;
    sdlRect.h = sdlSurface->h;
}

Text::~Text() {
    SDL_DestroyTexture(sdlTexture);
    SDL_FreeSurface(sdlSurface);
    TTF_CloseFont(ttfFont);
}

void Text::draw() {
    SDL_RenderCopy(sdlRenderer, sdlTexture, nullptr, &sdlRect);
}

void Text::draw(Vec2D pos) {
    sdlRect.x = pos.x;
    sdlRect.y = pos.y;
    SDL_RenderCopy(sdlRenderer, sdlTexture, nullptr, &sdlRect);
}

void Text::setColor(SDL_Color color) {
    this->color = color;
    SDL_Surface *oldSurface = sdlSurface;
    sdlSurface = TTF_RenderText_Blended(ttfFont, textContent.c_str(), color);
    SDL_FreeSurface(oldSurface);
}

void Text::setPos(Vec2D pos) {
    sdlRect.x = pos.x;
    sdlRect.y = pos.y;
}

void Text::setText(std::string newText) {
    textContent = newText;
    SDL_Surface *oldSurface = sdlSurface;
    sdlSurface = TTF_RenderText_Blended(ttfFont, textContent.c_str(), color);
    SDL_FreeSurface(oldSurface);
}

void Text::setPtSize(int ptSize) {
    this->ptSize = ptSize;
    TTF_Font *oldFont = ttfFont;
    ttfFont = TTF_OpenFont(fontPath.c_str(), ptSize);
    TTF_CloseFont(oldFont);
    if (!ttfFont) {
        throw std::runtime_error("Failed to load font");
    }
}
