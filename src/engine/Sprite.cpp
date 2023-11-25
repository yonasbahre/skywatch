#include <stdexcept>
#include <SDL2/SDL_image.h>
#include "Sprite.h"

Sprite::Sprite(SDL_Renderer *sdlRenderer, std::string spritePath) {
    this->sdlRenderer = sdlRenderer;
    this->spritePath = spritePath;
    this->sdlTexture = IMG_LoadTexture(sdlRenderer, spritePath.c_str());
    if (!sdlTexture) {
        throw std::runtime_error("Failed to load sprite");
    }
    SDL_QueryTexture(sdlTexture, nullptr, nullptr, &sdlRect.w, &sdlRect.h);
}

Sprite::~Sprite() {
    SDL_DestroyTexture(sdlTexture);
}

void Sprite::draw() {
    if (!isVisible) {
        return;
    }

    SDL_RenderCopy(sdlRenderer, sdlTexture, nullptr, &sdlRect);
}

void Sprite::draw(Vec2D pos) {
    if (!isVisible) {
        return;
    }

    setPos(pos);
    SDL_RenderCopy(sdlRenderer, sdlTexture, nullptr, &sdlRect);
}

void Sprite::setPos(Vec2D pos) {
    if (isCentered) {
        Vec2D offset = getDimensions() / Vec2D(2.0, 2.0);
        sdlRect.x = pos.x - offset.x;
        sdlRect.y = pos.y - offset.y;
        return;
    }

    sdlRect.x = pos.x;
    sdlRect.y = pos.y;
}

void Sprite::setDimensions(Vec2D pos) {
    sdlRect.w = pos.x;
    sdlRect.h = pos.y;
    // setPos(Vec2D(sdlRect.x, sdlRect.y));
}

void Sprite::scaleDimensions(float scaleFactor) {
    setDimensions(getDimensions() * Vec2D(scaleFactor, scaleFactor));
}

void Sprite::setIsCentered(bool isCentered) {
    this->isCentered = isCentered;
    
    Vec2D offset = getDimensions() / Vec2D(2.0, 2.0);
    setPos( isCentered
        ? Vec2D(sdlRect.x, sdlRect.y) - offset
        : Vec2D(sdlRect.x, sdlRect.y) + offset
    );
}

void Sprite::setIsVisible(bool isVisible) {
    this->isVisible = isVisible;
}

Vec2D Sprite::getDimensions() {
    return Vec2D(sdlRect.w, sdlRect.h);
}

std::vector<float> Sprite::getCorners() {
    return {
        float (sdlRect.x),
        float (sdlRect.y),
        float (sdlRect.x + sdlRect.w),
        float (sdlRect.y + sdlRect.h)
    };
}