#include <iostream>
#include "LevelMap.h"
#include "SDLUtils.h"

LevelMap::LevelMap(EngineObject *parent) : EngineObject(parent) {
    renderer = new LevelMapRenderer(this);
}

void LevelMap::start() {
    std::cout << "Starting level map!\n";
}

void LevelMap::update() {}

void LevelMap::updateScreenTransform(Vec2D playerWorldPos) {
    screenTransform = playerWorldPos + baseScreenTransform;
}

LevelMapRenderer::LevelMapRenderer(LevelMap *object) : Renderer(object) {}

void LevelMapRenderer::render() {
    LevelMap *lvlMap = dynamic_cast<LevelMap*>(object);
    // for (int x = 0; x < SCREEN_WIDTH; x++) {
    //     for (int y = 0; y < SCREEN_HEIGHT; y++) {
    //         setSDLDrawColor(
    //             sdlRenderer,
    //             ((x + (int)lvlMap->screenTransform.x) / 50) % 2 ^ ((y + (int)lvlMap->screenTransform.y)/ 50) % 2 
    //                 ? GRASS 
    //                 : DIRT
    //         );
    //         SDL_RenderDrawPoint(sdlRenderer, x, y);
    //     }
    // }

    int start = (int) lvlMap->screenTransform.x % 50;
    bool isGrass = (((int)lvlMap->screenTransform.x / 50) % 2);
    setSDLDrawColor(sdlRenderer, isGrass ? GRASS : DIRT);
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        if (start == 50) {
            start = 0;
            isGrass = !isGrass;
            setSDLDrawColor(
                sdlRenderer,
                isGrass ? GRASS : DIRT
            );
        }
            
        SDL_Rect currRect = {x, 0, 50, SCREEN_HEIGHT};
        SDL_RenderDrawRect(sdlRenderer, &currRect);
        start++;
    }
}