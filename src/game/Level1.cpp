#include <iostream>
#include "Level1.h"

Level1::Level1() {
    segments = 
        std::vector<std::unordered_set<EngineObject*>>(map.roadCoords.size());
}

Level1::~Level1() {
    for (int segmentIndex = 0; segmentIndex < segments.size(); segmentIndex++) {
        unloadSegment(segmentIndex);
    }
    segments.clear();
}

void Level1::start() {
    player.registerAndStart();
    sampleCrow.registerAndStart();
    sampleEnemy.registerAndStart();
    map.registerAndStart();
}

void Level1::update() {
    screenTransform = player.getWorldPos() + baseScreenTransform;
}

void Level1::loadSegment(int index) {
    if (index < 0 || index >= segments.size()) {
        return;
    }
}

void Level1::unloadSegment(int index) {
    if (index < 0 || index >= segments.size()) {
        return;
    }
    for (EngineObject *entity : segments[index]) {
        delete entity;
    }
    segments[index].clear();
}

std::function<int(Vec2D)> Level1::getRoadSegmentOfPoint() {
    return [this](Vec2D point) {
        float x1 = map.roadCoords[currSegment][0];
        float x2 = x1 + map.roadCoords[currSegment][2];
        float y1 = map.roadCoords[currSegment][1];
        float y2 = y1 + map.roadCoords[currSegment][3];
        
        if (
            point.x >= x1 &&
            point.x <= x2 &&
            point.y >= y1 &&
            point.y <= y2
        ) {
            return currSegment;
        }

        if (currSegment + 1 < map.roadCoords.size()) {
            x1 = map.roadCoords[currSegment + 1][0];
            x2 = x1 + map.roadCoords[currSegment + 1][2];
            y1 = map.roadCoords[currSegment + 1][1];
            y2 = y1 + map.roadCoords[currSegment + 1][3];

            if (
                point.x >= x1 &&
                point.x <= x2 &&
                point.y >= y1 &&
                point.y <= y2
            ) {
                return currSegment + 1;
            }
        }

        if (currSegment - 1 >= 0) {
            x1 = map.roadCoords[currSegment - 1][0];
            x2 = x1 + map.roadCoords[currSegment - 1][2];
            y1 = map.roadCoords[currSegment - 1][1];
            y2 = y1 + map.roadCoords[currSegment - 1][3];

            if (
                point.x >= x1 &&
                point.x <= x2 &&
                point.y >= y1 &&
                point.y <= y2
            ) {
                return currSegment - 1;
            }
        }

        return -1;
    };
}

std::function<void(int)> Level1::updateCurrRoadSegment() {
    return [this](int index) {
        if (currSegment == index) {
            return;
        }
        int prevSegment = currSegment;
        currSegment = index;

        if (prevSegment < currSegment) {
            loadSegment(currSegment + RIGHT_WINDOW_SIZE);
            unloadSegment(currSegment - LEFT_WINDOW_SIZE - 1);
        } else {
            loadSegment(currSegment - LEFT_WINDOW_SIZE);
            unloadSegment(currSegment + RIGHT_WINDOW_SIZE + 1);
        }
    };
}