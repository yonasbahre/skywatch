#pragma once
#include <string>
#include <vector>
#include <functional>
#include "Sprite.h"
#include "Collision.h"

class CollisionManager;

class Collider {
    CollisionManager *manager = nullptr;
    std::vector<Collision> collisions;
    Sprite *sprite = nullptr;

    void removeCollisionWith(Collider &collider);

public:
    Collider(Sprite &sprite);
    ~Collider();

    std::string tag;
    std::function<void(Collision&)> onCollisionStart = [](Collision&){};

    std::vector<float> getCorners(); 
    bool isColliding(Collider &other);
    void updateCollisionState(Collider &other);
};

