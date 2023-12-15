#pragma once
#include "Crow.h"

class CrowState {
public:
    Crow *crow;

    CrowState(Crow *crow_);

    // For some reason, the reference to the crow becomes invalid after construction
    // So we update the reference each frame
    virtual void update(Crow *crow) = 0;
};

class CrowIdleState : public CrowState {
    const float MAX_IDLE_DIST = 125;
    const float IDLE_SPEED = 0.5;

    Vec2D velocity = {0, 0};
public:
    CrowIdleState(Crow *crow_);
    void update(Crow *crow);
};

class CrowGiftingPebbleState : public CrowState {
    const float SPEED = 0.7;
    Vec2D velocity = {0, 0};

public:
    CrowGiftingPebbleState(Crow *crow_);
    void update(Crow *crow);
};