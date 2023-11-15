#include <iostream>
#include <algorithm>
#include <string>

#include "Engine.h"
#include "Constants.h"

#include <SDL2/SDL_ttf.h>

Engine *Engine::engineSingleton = nullptr;

Engine::Engine() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    
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
}

Engine::~Engine() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    for (EngineObject *obj : globalObjects) {
        delete obj;
    }
    delete currLevel;
    delete eventMgr;

    TTF_Quit();
    SDL_Quit();
    delete engineSingleton;
}

Engine *Engine::getEngine() {
    if (!engineSingleton) {
        engineSingleton = new Engine();
    }
    return engineSingleton;
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
    std::function<EngineObject*()> lvlConstructor = levelRegistry[levelId];

    EngineObject *oldLevel = currLevel;
    EngineObject *newLevel = lvlConstructor();

    // NOTE: Must put mutex around these two lines if we ever
    // make this engine multithreaded
    currLevel = newLevel;
    currLevel->start();

    delete oldLevel;
}

void Engine::setStartLevel(const std::string& levelId) {
    startLevelId = levelId;
}

inline void Engine::start() {
    loadLevel(startLevelId);
    SDL_ShowWindow(window);
}

inline void Engine::update() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
        }
    }
    eventMgr->updateEvents();

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
}

inline void Engine::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    std::vector<EngineObject*> stack = globalObjects;
    if (currLevel) {
        stack.push_back(currLevel);
    }
    while (!stack.empty()) {
        EngineObject *curr = stack.back();
        stack.pop_back();

        if (curr->renderer) {
            curr->renderer->updateGlobalPosAndRender();
        }
        for (EngineObject *child : curr->children) {
            stack.push_back(child);
        }
    }

    SDL_RenderPresent(renderer);
}

int Engine::run() {
    start();

    while (!quit) {
        update();
        render();
    }

    return EXIT_SUCCESS;
}