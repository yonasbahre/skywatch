#include <iostream>
#include "Level1.h"
#include "Utils.h"
#include "Enemy.h"
#include "Crow.h"
#include "Bread.h"
#include "Pebble.h"
#include "Projectile.h"

Level1::Level1() {
    segments = 
        std::vector<std::unordered_set<EngineObject*>>(map.roadCoords.size());

    for (int segment = 0; segment <= RIGHT_WINDOW_SIZE; segment++) {
        loadSegment(segment);
    }
}

Level1::~Level1() {
    for (int segmentIndex = 0; segmentIndex < segments.size(); segmentIndex++) {
        unloadSegment(segmentIndex);
    }
    segments.clear();
}

void Level1::start() {
    ui.registerAndStart();
    player.registerAndStart();
    segmentParent.registerAndStart();
    map.registerAndStart();
    for (int segment = 0; segment <= RIGHT_WINDOW_SIZE; segment++) {
        startSegment(segment);
    }
}

void Level1::update() {
    for (EngineObject *object : deletionQueue) {
        deleteObjectFromSegment(object);
    }
    deletionQueue.clear();

    screenTransform = player.getWorldPos() + baseScreenTransform;
}

void Level1::loadSegment(int index) {
    if (index < 0 || index >= segments.size()) {
        return;
    }

    loadEnemiesInSegment(index);
    loadCrowsInSegment(index);
    loadBreadInSegment(index);
    loadPebblesInSegment(index);
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

void Level1::startSegment(int index) {
    if (index < 0 || index >= segments.size()) {
        return;
    }
    for (EngineObject *entity : segments[index]) {
        entity->registerAndStart();
    }
}

void Level1::loadEnemiesInSegment(int index) {
    std::vector<float> roadRect = map.roadCoords[index];
    float longSideLength = std::max(roadRect[2], roadRect[3]);
    float segmentLengthThreshold = (map.MIN_SEGMENT_DIST + map.MAX_SEGMENT_DIST) / 1.5;

    if (index == 0) {
        return;
    }

    // Only load 1 enemy in this segment if the segment is small enough
    if (longSideLength < segmentLengthThreshold) {
        Enemy *newEnemy = new Enemy(&segmentParent, screenTransform);
        newEnemy->pos = {
            roadRect[0] + (float) randInt(0, (int) roadRect[2]),
            roadRect[1] + (float) randInt(0, (int) roadRect[3])
        };
        newEnemy->onDestroy = queueForDeletion();
        segments[index].insert(newEnemy);
        return;
    }

    float length1 = (float) randInt(0, (int) longSideLength / 2);
    float length2 = (float) randInt((int) longSideLength / 2, (int) longSideLength);
    Vec2D pos1 = {0, 0}, pos2 = {0, 0};
    
    if (longSideLength == roadRect[2]) {
        pos1 = {
            roadRect[0] + length1,
            roadRect[1] + (float) randInt(0, (int) roadRect[3])
        };
        pos2 = {
            roadRect[0] + length2,
            roadRect[1] + (float) randInt(0, (int) roadRect[3])
        };
    } else {
        pos1 = {
            roadRect[0] + (float) randInt(0, (int) roadRect[2]),
            roadRect[1] + length1
        };
        pos2 = {
            roadRect[0] + (float) randInt(0, (int) roadRect[2]),
            roadRect[1] + length2
        };
    }

    Enemy *newEnemy1 = new Enemy(&segmentParent, screenTransform);
    newEnemy1->pos = pos1;
    newEnemy1->onDestroy = queueForDeletion();
    Enemy *newEnemy2 = new Enemy(&segmentParent, screenTransform);
    newEnemy2->pos = pos2;
    newEnemy2->onDestroy = queueForDeletion();

    segments[index].insert(newEnemy1);
    segments[index].insert(newEnemy2);
}

void Level1::loadCrowsInSegment(int index) {
    std::vector<float> roadRect = map.roadCoords[index];
    float longSideLength = std::max(roadRect[2], roadRect[3]);
    float segmentLengthThreshold = (map.MIN_SEGMENT_DIST + map.MAX_SEGMENT_DIST) / 2;

    // Only load 1 crow in this segment if the segment is small enough
    if (longSideLength < segmentLengthThreshold) {
        Crow *newCrow = new Crow(&segmentParent, screenTransform);
        newCrow->pos = {
            roadRect[0] + (float) randInt(0, (int) roadRect[2]),
            roadRect[1] + (float) randInt(0, (int) roadRect[3])
        };
        newCrow->onDestroy = queueForDeletion();
        segments[index].insert(newCrow);
        return;
    }

    float length1 = (float) randInt(0, (int) longSideLength / 2);
    float length2 = (float) randInt((int) longSideLength / 2, (int) longSideLength);
    Vec2D pos1 = {0, 0}, pos2 = {0, 0};
    
    if (longSideLength == roadRect[2]) {
        pos1 = {
            roadRect[0] + length1,
            roadRect[1] + (float) randInt(0, (int) roadRect[3])
        };
        pos2 = {
            roadRect[0] + length2,
            roadRect[1] + (float) randInt(0, (int) roadRect[3])
        };
    } else {
        pos1 = {
            roadRect[0] + (float) randInt(0, (int) roadRect[2]),
            roadRect[1] + length1
        };
        pos2 = {
            roadRect[0] + (float) randInt(0, (int) roadRect[2]),
            roadRect[1] + length2
        };
    }

    Crow *newCrow1 = new Crow(&segmentParent, screenTransform);
    newCrow1->pos = pos1;
    newCrow1->onDestroy = queueForDeletion();
    Crow *newCrow2 = new Crow(&segmentParent, screenTransform);
    newCrow2->pos = pos2;
    newCrow2->onDestroy = queueForDeletion();

    segments[index].insert(newCrow1);
    segments[index].insert(newCrow2);
}

void Level1::loadBreadInSegment(int index) {
    std::vector<float> roadRect = map.roadCoords[index];

    for (int i = 0; i < 2; i++) {
        bool decideToSpawn = randInt(0, 10) > 7;
        if (!decideToSpawn) {
            continue;
        }

        Bread *newBread = new Bread(&segmentParent, screenTransform);
        newBread->getRenderer()->pos = {
            roadRect[0] + (float) randInt(0, (int) roadRect[2]),
            roadRect[1] + (float) randInt(0, (int) roadRect[3])
        };
        newBread->onDestroy = queueForDeletion();

        segments[index].insert(newBread);
    }
}

void Level1::loadPebblesInSegment(int index) {
    std::vector<float> roadRect = map.roadCoords[index];

    bool decideToSpawn = randInt(0, 10) > 8;
    if (!decideToSpawn) {
        return;
    }

    Pebble *newPebble = new Pebble(&segmentParent, screenTransform);
    newPebble->getRenderer()->pos = {
        roadRect[0] + (float) randInt(0, (int) roadRect[2]),
        roadRect[1] + (float) randInt(0, (int) roadRect[3])
    };
    newPebble->onDestroy = queueForDeletion();

    segments[index].insert(newPebble);  
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
            startSegment(currSegment + RIGHT_WINDOW_SIZE);
        } else {
            loadSegment(currSegment - LEFT_WINDOW_SIZE);
            unloadSegment(currSegment + RIGHT_WINDOW_SIZE + 1);
            startSegment(currSegment - LEFT_WINDOW_SIZE);
        }
    };
}

std::function<void(EngineObject*)> Level1::queueForDeletion() {
    return [this](EngineObject *object) {
        deletionQueue.push_back(object);
    };
}

void Level1::deleteObjectFromSegment(EngineObject *object) {
    for (
        int segment = std::max(0, currSegment - LEFT_WINDOW_SIZE);
        segment <= std::min((int) segments.size() - 1, currSegment + RIGHT_WINDOW_SIZE);
        segment++
    ) {
        auto iter = segments[segment].find(object);
        if (iter == segments[segment].end()) {
            continue;
        }

        segments[segment].erase(iter);
        delete object;
    }
}

std::function<void(Direction)> Level1::fireProjectileCallback() {
    return [this](Direction lastDirection) {
        Projectile *projectile = new Projectile(
            &segmentParent, 
            screenTransform,
            player.getWorldPos() * Vec2D(-1, -1),
            lastDirection
        );
        projectile->registerAndStart();
    };
}