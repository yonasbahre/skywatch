#pragma once
#include <vector>
#include "Vec2D.h"

struct Incident {
    float score;
    Vec2D position = {0, 0};
    long long timestamp;
};

/**
 * This class simulates the crows communicating over distance & time.
 */
class CrowField {
    std::vector<Incident> incidents;

public:
    const float POSITIVE_INTERACTION = 1000;
    const float NEGATIVE_INTERACTION = -5000;
    const float VERY_NEGATIVE_INTERACTION = -10000;

    // pixels per millisecond
    const float SPREAD_SPEED = 500 / 1000;

    void addIncident(float score, Vec2D position);
    float getAgitation(Vec2D position);
};