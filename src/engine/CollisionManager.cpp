#include "Collider.h"
#include "CollisionManager.h"
#include <algorithm>

CollisionManager::CollisionManager() {}

CollisionManager::~CollisionManager() {}

CollisionManager *CollisionManager::getGlobalManager() {
    static CollisionManager globalManager;
    return &globalManager;
}

void CollisionManager::registerCollider(Collider &collider) {
    colliders.push_back(&collider);
}

void CollisionManager::deregisterCollider(Collider &collider) {
    auto iter = std::find(colliders.begin(), colliders.end(), &collider);
    if (iter != colliders.end()) {
        colliders.erase(iter);
    }
}

void CollisionManager::update() {
    for (size_t i = 0; i < colliders.size(); i++) {
        for (size_t j = i + 1; j < colliders.size(); j++) {
            colliders[i]->updateCollisionState(*colliders[j]);
        }
    }
}