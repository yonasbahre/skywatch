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

LevelMapRenderer::LevelMapRenderer(LevelMap *object) : Renderer(object) {
    lvlMap = object;
}

void LevelMapRenderer::render() {
    setSDLDrawColor(sdlRenderer, {0, 0, 255, 255});
    SDL_Rect screenRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    int status = SDL_RenderDrawRect(sdlRenderer, &screenRect);

    for (std::vector<float>& road : lvlMap->roadCoords) {
        renderRoad(road);
    }
    // int start = (int) lvlMap->screenTransform.x % 50;
    // bool isGrass = (((int)lvlMap->screenTransform.x / 50) % 2);
    // setSDLDrawColor(sdlRenderer, isGrass ? GRASS : DIRT);
    // for (int x = 0; x < SCREEN_WIDTH; x++) {
    //     if (start == 50) {
    //         start = 0;
    //         isGrass = !isGrass;
    //         setSDLDrawColor(
    //             sdlRenderer,
    //             isGrass ? GRASS : DIRT
    //         );
    //     }
            
    //     SDL_Rect currRect = {x, 0, 50, SCREEN_HEIGHT};
    //     SDL_RenderDrawRect(sdlRenderer, &currRect);
    //     start++;
    // }
}

void LevelMapRenderer::renderRoad(std::vector<float>& road) {
    // setSDLDrawColor(sdlRenderer, DIRT);
    // float halfWidth = lvlMap->roadWidth / 2;

    // SDL_Rect roadRect;
    // roadRect.x = road[0] + lvlMap->screenTransform.x - halfWidth;
    // roadRect.y = road[1] + lvlMap->screenTransform.y - halfWidth;
    // roadRect.w = road[2] - road[0] + halfWidth + halfWidth;
    // roadRect.h = road[3] - road[1] + halfWidth + halfWidth;

    // SDL_RenderDrawRect(sdlRenderer, &roadRect);
}