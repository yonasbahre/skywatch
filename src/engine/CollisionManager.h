#pragma once
#include <vector>

class Collider;

class CollisionManager {
    std::vector<Collider*> colliders;
    
    CollisionManager();
public:
    ~CollisionManager();

    static CollisionManager *getGlobalManager();

    void registerCollider(Collider &collider);
    void deregisterCollider(Collider &collider);

    void update();
};