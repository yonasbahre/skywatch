#pragma once
#include <vector>
#include <unordered_map>
#include <functional>
#include <SDL2/SDL.h>
#include "EngineObject.h"
#include "EventManager.h"

class Engine {
    static Engine *engineSingleton;
    Engine();

    std::unordered_map<std::string, std::function<EngineObject*()>> levelRegistry;
    std::string startLevelId;

    bool quit = false;
    EngineObject *currLevel = nullptr;
    std::vector<EngineObject*> globalObjects;
    EventManager *eventMgr = nullptr;

    void start();
    void update();
    void render();
public:
    ~Engine();
    static Engine *getEngine();

    void registerGlobalObject(EngineObject *obj);
    void deregisterGlobalObject(EngineObject *obj);
    
    void registerLevel(
        const std::string& levelId,
        std::function<EngineObject*()> lvlConstructor
    );
    void loadLevel(const std::string& levelId);
    void setStartLevel(const std::string& levelId);

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    int run();
};