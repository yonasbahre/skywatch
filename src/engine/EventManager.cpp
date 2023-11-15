#include "EventManager.h"

EventManager *EventManager::managerSingleton = nullptr;

EventManager::EventManager() {
    keyStates = SDL_GetKeyboardState(&keyStatesLength);
}

EventManager::~EventManager() {
    delete managerSingleton;
}

EventManager *EventManager::getManager() {
    if (!managerSingleton) {
        managerSingleton = new EventManager();
    }
    return managerSingleton;
}
