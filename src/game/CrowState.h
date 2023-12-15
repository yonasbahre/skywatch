#pragma once
#include "Crow.h"

class CrowState {
public:
    Crow *crow;

    CrowState(Crow *crow_);
    virtual void update() = 0;
};

class CrowIdleState : public CrowState {
    const float MAX_IDLE_DIST = 350;
    const float IDLE_SPEED = 0.5;

    Vec2D velocity = {0, 0};
public:
    CrowIdleState(Crow *crow_);
    void update();
};