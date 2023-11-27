#include <algorithm>
#include "CollisionManager.h"
#include "Collider.h"

#include <iostream>

Collider::Collider(Sprite &sprite) {
    this->sprite = &sprite;
    manager = CollisionManager::getGlobalManager();
    manager->registerCollider(*this);
}

Collider::~Collider() {
    for (Collision& collision : collisions) {
        collision.other->removeCollisionWith(*this);
    }
    manager->deregisterCollider(*this);
}

std::vector<float> Collider::getCorners() {
    return sprite->getCorners();
}

bool Collider::isColliding(Collider &other) {
    std::vector<float> ourCorners_ = getCorners();
    std::vector<Vec2D> ourCorners = {
        {ourCorners_[0], ourCorners_[1]},
        {ourCorners_[0], ourCorners_[3]},
        {ourCorners_[2], ourCorners_[1]},
        {ourCorners_[2], ourCorners_[3]}
    };

    std::vector<float> otherCorners = other.getCorners();
    for (Vec2D& corner : ourCorners) {
        if (
            corner.x >= otherCorners[0] &&
            corner.x <= otherCorners[2] &&
            corner.y >= otherCorners[1] &&
            corner.y <= otherCorners[3]
        ) {
            return true;
        }
    }

    return false;
}

void Collider::updateCollisionState(Collider &other) {
    Collider *otherAddr = &other;
    auto thisCollision = std::find_if(
        collisions.begin(),
        collisions.end(),
        [otherAddr](Collision &col){ return col.other == otherAddr; }
    );
    
    bool colliding = isColliding(other);
    
    if (!colliding && thisCollision != collisions.end()) {
        thisCollision->other->removeCollisionWith(*this);
        collisions.erase(thisCollision);
        std::cout << "Collision ended and removed!\n";
    } 
    else if (colliding && thisCollision == collisions.end()) {
        collisions.push_back({&other});
        other.collisions.push_back({this});
        
        onCollisionStart(collisions.back());
        other.onCollisionStart(other.collisions.back());
        std::cout << "Collision processed!\n";
    }
}

void Collider::removeCollisionWith(Collider &collider) {
    Collider *colliderAddr = &collider;
    auto collision = std::find_if(
        collisions.begin(),
        collisions.end(),
        [colliderAddr](Collision &col){ return col.other == colliderAddr; }
    );

    if (collision != collisions.end()) {
        collisions.erase(collision);
    }
}
