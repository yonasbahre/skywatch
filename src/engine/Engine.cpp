#include <iostream>
#include <algorithm>
#include <string>
#include <chrono>

#include "Engine.h"
#include "Constants.h"

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

Engine::Engine() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);
    
    window = SDL_CreateWindow(
        "Skywatch", 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT ,
        SDL_WINDOW_HIDDEN  
    );
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    eventMgr = EventManager::getManager();
    collisionMgr = CollisionManager::getGlobalManager();
}

Engine::~Engine() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    for (EngineObject *obj : globalObjects) {
        delete obj;
    }
    delete currLevel;
    delete collisionMgr;
    delete eventMgr;

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

Engine *Engine::getEngine() {
    static Engine engine;
    return &engine;
}

void Engine::registerGlobalObject(EngineObject *obj) {
    globalObjects.push_back(obj);
}

void Engine::deregisterGlobalObject(EngineObject *obj) {
    auto iter = std::find(globalObjects.begin(), globalObjects.end(), obj);
    if (iter != globalObjects.end()) {
        globalObjects.erase(iter);
    }
}

void Engine::registerLevel(
    const std::string& levelId,
    std::function<EngineObject*()> lvlConstructor
) {
    levelRegistry[levelId] = lvlConstructor;
}

void Engine::loadLevel(const std::string& levelId) {
    // Level won't actually be loaded until
    // start of next frame
    queuedLevel = levelId;
}

void Engine::setStartLevel(const std::string& levelId) {
    startLevelId = levelId;
}

inline void Engine::start() {
    loadLevel(startLevelId);
    SDL_ShowWindow(window);
}

inline void Engine::update() {
    if (queuedLevel) {
        std::function<EngineObject*()> lvlConstructor = levelRegistry[queuedLevel.value()];
        EngineObject *oldLevel = currLevel;
        currLevel = lvlConstructor();
        delete oldLevel;
        currLevel->start();
        queuedLevel = std::nullopt;
    }

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                return;
        }
    }
    eventMgr->updateEvents();
    if (eventMgr->keyStates[SDL_SCANCODE_ESCAPE]) {
        quit = true;
        return;
    }

    std::vector<EngineObject*> stack = globalObjects;
    if (currLevel) {
        stack.push_back(currLevel);
    }
    while (!stack.empty()) {
        EngineObject *curr = stack.back();
        stack.pop_back();

        curr->update();
        for (EngineObject *child : curr->children) {
            stack.push_back(child);
        }
    }

    collisionMgr->update();
}

inline void Engine::render() {
    if (quit) {
        return;
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    std::vector<EngineObject*> stack = globalObjects;
    if (currLevel) {
        stack.push_back(currLevel);
    }
    while (!stack.empty()) {
        EngineObject *curr = stack.back();
        stack.pop_back();

        if (curr->getRenderer()) {
            curr->getRenderer()->updateGlobalPosAndRender();
        }
        for (EngineObject *child : curr->children) {
            stack.push_back(child);
        }
    }

    SDL_RenderPresent(renderer);
}

int Engine::run() {
    using namespace std::chrono;
    start();

    while (!quit) {
        milliseconds frameStartTime = duration_cast<milliseconds>(
            system_clock::now().time_since_epoch()
        );
        long long frameEndTime = frameStartTime.count() + FRAME_TIME_MILLISECONDS;

        update();
        render();

        do {
            milliseconds now = duration_cast<milliseconds>(
                system_clock::now().time_since_epoch()
            );
            if (now.count() >= frameEndTime) {
                break;
            }
        } while (true);
    }

    return EXIT_SUCCESS;
}