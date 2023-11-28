#include "EventManager.h"

EventManager::EventManager() {
    keyStates = SDL_GetKeyboardState(&keyStatesLength);
}

EventManager::~EventManager() {}

EventManager *EventManager::getManager() {
    static EventManager manager;
    return &manager;
}
