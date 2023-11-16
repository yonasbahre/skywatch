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
    if (!sdlSurface) {
        throw std::runtime_error("Failed to load surface");
    }
    sdlTexture = SDL_CreateTextureFromSurface(sdlRenderer, sdlSurface);
    if (!sdlTexture) {
        throw std::runtime_error("Failed to load texture");
    }
    sdlRect.w = sdlSurface->w;
    sdlRect.h = sdlSurface->h;
}

Text::~Text() {
    SDL_DestroyTexture(sdlTexture);
    SDL_FreeSurface(sdlSurface);
    TTF_CloseFont(ttfFont);
}

void Text::draw() {
    if (!isVisible) {
        return;
    }

    SDL_RenderCopy(sdlRenderer, sdlTexture, nullptr, &sdlRect);
}

void Text::draw(Vec2D pos) {
    if (!isVisible) {
        return;
    }

    setPos(pos);
    SDL_RenderCopy(sdlRenderer, sdlTexture, nullptr, &sdlRect);
}

void Text::setColor(SDL_Color color) {
    this->color = color;
    updateSurfaceAndTexture();
}

void Text::setPos(Vec2D pos) {
    if (isCentered) {
        Vec2D offset = getDimensions() / Vec2D(2.0, 2.0);
        sdlRect.x = pos.x - offset.x;
        sdlRect.y = pos.y - offset.y;
        return;
    }

    sdlRect.x = pos.x;
    sdlRect.y = pos.y;
}

void Text::setText(std::string newText) {
    textContent = newText;
    TTF_SizeText(ttfFont, textContent.c_str(), &sdlRect.w, &sdlRect.h);
    updateSurfaceAndTexture();
}

void Text::setPtSize(int ptSize) {
    this->ptSize = ptSize;
    TTF_Font *oldFont = ttfFont;
    ttfFont = TTF_OpenFont(fontPath.c_str(), ptSize);
    TTF_CloseFont(oldFont);
    if (!ttfFont) {
        throw std::runtime_error("Failed to load font");
    }
    updateSurfaceAndTexture();
}

void Text::setIsCentered(bool isCentered) {
    this->isCentered = isCentered;
    
    Vec2D offset = getDimensions() / Vec2D(2.0, 2.0);
    setPos( isCentered
        ? Vec2D(sdlRect.x, sdlRect.y) - offset
        : Vec2D(sdlRect.x, sdlRect.y) + offset
    );
}

void Text::setIsVisible(bool isVisible) {
    this->isVisible = isVisible;
}

Vec2D Text::getDimensions() {
    return Vec2D(sdlRect.w, sdlRect.h);
}

bool Text::getIsVisible() {
    return isVisible;
}

void Text::updateSurfaceAndTexture() {
    SDL_Surface *oldSurface = sdlSurface;
    sdlSurface = TTF_RenderText_Blended(ttfFont, textContent.c_str(), color);
    SDL_Texture *oldTexture = sdlTexture;
    sdlTexture = SDL_CreateTextureFromSurface(sdlRenderer, sdlSurface);
    SDL_DestroyTexture(oldTexture);
    SDL_FreeSurface(oldSurface);
}