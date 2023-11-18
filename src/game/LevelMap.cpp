#include <iostream>
#include <ctime>
#include <random>
#include "LevelMap.h"
#include "SDLUtils.h"

LevelMap::LevelMap(EngineObject *parent) : EngineObject(parent) {
    renderer = new LevelMapRenderer(this);
    generateRoads();
}

void LevelMap::start() {}

void LevelMap::update() {}

void LevelMap::updateScreenTransform(Vec2D playerWorldPos) {
    screenTransform = playerWorldPos + baseScreenTransform;
}

int LevelMap::randInt(int min, int max) {
    static std::mt19937 eng(time(nullptr));
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(eng);
}

void LevelMap::generateRoads() {
    startPoint = Vec2D(0, 0);
    endPoint = Vec2D(
        randInt(MIN_TOTAL_DIST, MAX_TOTAL_DIST), 
        randInt(MIN_TOTAL_DIST, MAX_TOTAL_DIST)
    );

    Vec2D directions(
        randInt(0, 1) ? 1 : -1,
        randInt(0, 1) ? 1 : -1
    );
    endPoint = endPoint * directions;

    bool horizontal = randInt(0, 1);
    Vec2D currStart = startPoint;
    Vec2D currEnd = startPoint;
    
    while (
        std::abs((int) currEnd.x) < std::abs((int) endPoint.x) && 
        std::abs((int) currEnd.y) < std::abs((int) endPoint.y)
    ) {
        Vec2D displacement = horizontal
            ? Vec2D(randInt(MIN_SEGMENT_DIST, MAX_SEGMENT_DIST), 0)
            : Vec2D(0, randInt(MIN_SEGMENT_DIST, MAX_SEGMENT_DIST));
        
        displacement = displacement * directions;
        currEnd = currStart + displacement;
        roadCoords.push_back({currStart.x, currStart.y, currEnd.x, currEnd.y});
        
        horizontal = !horizontal;
        currStart = currEnd;
    }
    endPoint = currEnd;
}

LevelMapRenderer::LevelMapRenderer(LevelMap *object) : Renderer(object) {
    lvlMap = object;
}

void LevelMapRenderer::render() {
    setSDLDrawColor(sdlRenderer, GRASS);
    SDL_Rect screenRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderFillRect(sdlRenderer, &screenRect);

    for (std::vector<float>& road : lvlMap->roadCoords) {
        renderRoad(road);
    }
}

void LevelMapRenderer::renderRoad(std::vector<float>& road) {
    setSDLDrawColor(sdlRenderer, DIRT);
    float fullWidth = lvlMap->ROAD_WIDTH;
    float halfWidth = fullWidth / 2;

    SDL_Rect roadRect;
    float xDiff = road[2] - road[0];
    float yDiff = road[3] - road[1];

    if (xDiff >= 0) {
        roadRect.x = road[0] - halfWidth;
        roadRect.w = xDiff + fullWidth;
    } else {
        roadRect.x = road[2] - halfWidth;
        roadRect.w = (-1 * xDiff) + fullWidth;
    }

    if (yDiff >= 0) {
        roadRect.y = road[1] - halfWidth;
        roadRect.h = yDiff + fullWidth;
    } else {
        roadRect.y = road[3] - halfWidth;
        roadRect.h = (-1 * yDiff) + fullWidth;
    }

    roadRect.x += lvlMap->screenTransform.x;
    roadRect.y += lvlMap->screenTransform.y;

    SDL_RenderFillRect(sdlRenderer, &roadRect);
}