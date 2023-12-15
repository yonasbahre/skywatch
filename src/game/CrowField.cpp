#include <chrono>
#include <cmath>
#include <algorithm>
#include "CrowField.h"

void CrowField::addIncident(float score, Vec2D position) {
    using namespace std::chrono;
    
    Incident newIncident;
    newIncident.score = score;
    newIncident.position = position;

    milliseconds now = duration_cast<milliseconds>(
        system_clock::now().time_since_epoch()
    );
    newIncident.timestamp = now.count();

    incidents.push_back(newIncident);
}

float CrowField::getAgitation(Vec2D position) {
    using namespace std::chrono;
    float agitation = 0;

    long long now = duration_cast<milliseconds>(
        system_clock::now().time_since_epoch()
    ).count();

    for (Incident &incident : incidents) {
        Vec2D distance = position - incident.position;
        Vec2D absDistance = {std::abs(distance.x), std::abs(distance.y)};

        long long timeDiff = now - incident.timestamp;
        float spreadRadius = timeDiff * SPREAD_SPEED;
        
        Vec2D distAfterSpread = {
            std::max(0.0f, absDistance.x - spreadRadius),
            std::max(0.0f, absDistance.y - spreadRadius)
        };

        float distMagnitude = std::sqrt(
            (std::pow(distAfterSpread.x, 2.0)) + (std::pow(distAfterSpread.y, 2.0))
        );

        float thisAgitation = (200 * incident.score) / (distMagnitude + 1);
        agitation += thisAgitation;
    }

    return agitation;
}