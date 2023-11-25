#include <iostream>
#include "Level1.h"

Level1::Level1() {}

Level1::~Level1() {}

void Level1::start() {
    player.registerAndStart();
    map.registerAndStart();
}

void Level1::update() {
    map.updateScreenTransform(player.getWorldPos());
}

std::function<int(Vec2D)> Level1::getRoadIndexOfPoint() {
    return [this](Vec2D point) {
        float x1 = map.roadCoords[roadIndex][0];
        float x2 = x1 + map.roadCoords[roadIndex][2];
        float y1 = map.roadCoords[roadIndex][1];
        float y2 = y1 + map.roadCoords[roadIndex][3];
        
        if (
            point.x >= x1 &&
            point.x <= x2 &&
            point.y >= y1 &&
            point.y <= y2
        ) {
            return roadIndex;
        }

        if (roadIndex + 1 < map.roadCoords.size()) {
            x1 = map.roadCoords[roadIndex + 1][0];
            x2 = x1 + map.roadCoords[roadIndex + 1][2];
            y1 = map.roadCoords[roadIndex + 1][1];
            y2 = y1 + map.roadCoords[roadIndex + 1][3];

            if (
                point.x >= x1 &&
                point.x <= x2 &&
                point.y >= y1 &&
                point.y <= y2
            ) {
                return roadIndex + 1;
            }
        }

        if (roadIndex - 1 >= 0) {
            x1 = map.roadCoords[roadIndex - 1][0];
            x2 = x1 + map.roadCoords[roadIndex - 1][2];
            y1 = map.roadCoords[roadIndex - 1][1];
            y2 = y1 + map.roadCoords[roadIndex - 1][3];

            if (
                point.x >= x1 &&
                point.x <= x2 &&
                point.y >= y1 &&
                point.y <= y2
            ) {
                return roadIndex - 1;
            }
        }

        return -1;
    };
}

std::function<void(int)> Level1::updateRoadIndex() {
    return [this](int index) {
        roadIndex = index;
    };
}