#include <chrono>
#include <cmath>
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
        float distMagnitude = std::sqrt(
            (distance.x * distance.x) + (distance.y * distance.y)
        );

        long long timeDiff = now - incident.timestamp;
        float spreadRadius = timeDiff * SPREAD_SPEED;

        float thisAgitation = incident.score / (distMagnitude - spreadRadius);
        agitation += thisAgitation;
    }

    return agitation;
}