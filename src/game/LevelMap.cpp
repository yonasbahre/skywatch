#include <iostream>
#include <ctime>
#include <random>
#include "LevelMap.h"
#include "SDLUtils.h"

LevelMap::LevelMap(EngineObject *parent, Vec2D const &screenTransform_) 
    : EngineObject(parent), screenTransform(screenTransform_) {
    renderer = new LevelMapRenderer(this);
    generateRoads();
}

LevelMap::~LevelMap() {}

void LevelMap::start() {}

void LevelMap::update() {}

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

        // New code for reformatting road storage
        // TODO: Clean this up, no need to recalculate xDiff and yDiff
        // Everything inside this while loop could be cleaned up honestly
        std::vector<float> currRoad(4);
        float xDiff = currEnd.x - currStart.x;
        float yDiff = currEnd.y - currStart.y;
        const float HALF_ROAD_WIDTH = ROAD_WIDTH / 2;

        if (xDiff >= 0) {
            currRoad[0] = currStart.x - HALF_ROAD_WIDTH;
            currRoad[2] = xDiff + ROAD_WIDTH;
        } else {
            currRoad[0] = currEnd.x - HALF_ROAD_WIDTH;
            currRoad[2] = (-1 * xDiff) + ROAD_WIDTH;
        }

        if (yDiff >= 0) {
            currRoad[1] = currStart.y - HALF_ROAD_WIDTH;
            currRoad[3] = yDiff + ROAD_WIDTH;
        } else {
            currRoad[1] = currEnd.y - HALF_ROAD_WIDTH;
            currRoad[3] = (-1 * yDiff) + ROAD_WIDTH;
        }

        roadCoords.push_back(currRoad);        
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
    SDL_Rect roadRect = 
        {(int) road[0], (int) road[1], (int) road[2], (int) road[3]};
    
    roadRect.x += lvlMap->screenTransform.x;
    roadRect.y += lvlMap->screenTransform.y;

    SDL_RenderFillRect(sdlRenderer, &roadRect);
}