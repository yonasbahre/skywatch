#include "Collider.h"
#include "CollisionManager.h"
#include <algorithm>

#include <iostream>

CollisionManager::CollisionManager() {}

CollisionManager::~CollisionManager() {}

CollisionManager *CollisionManager::getGlobalManager() {
    static CollisionManager globalManager;
    return &globalManager;
}

void CollisionManager::registerCollider(Collider &collider) {
    colliders.push_back(&collider);
    std::cout << "Add - Collider Count: " << colliders.size() << std::endl;
}

void CollisionManager::deregisterCollider(Collider &collider) {
    auto iter = std::find(colliders.begin(), colliders.end(), &collider);
    if (iter != colliders.end()) {
        colliders.erase(iter);
    }
    std::cout << "Del - Collider Count: " << colliders.size() << std::endl;
}

void CollisionManager::update() {
    for (size_t i = 0; i < colliders.size(); i++) {
        for (size_t j = i + 1; j < colliders.size(); j++) {
            colliders[i]->updateCollisionState(*colliders[j]);
        }
    }
}