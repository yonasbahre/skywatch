#pragma once
#include <SDL2/SDL.h>

class EventManager {
    static EventManager *managerSingleton;
    EventManager();

    int keyStatesLength = 0;

public:
    ~EventManager();
    static EventManager *getManager();

    const unsigned char *keyStates;

    inline void updateEvents() {
        SDL_PumpEvents();
    }
};