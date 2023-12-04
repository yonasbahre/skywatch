#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <functional>
#include <optional>
#include <SDL2/SDL.h>
#include "EngineObject.h"
#include "EventManager.h"
#include "CollisionManager.h"

class Engine {
    Engine();

    std::unordered_map<std::string, std::function<EngineObject*()>> levelRegistry;
    std::string startLevelId;

    bool quit = false;
    EngineObject *currLevel = nullptr;
    std::optional<std::string> queuedLevel;

    std::vector<EngineObject*> globalObjects;
    EventManager *eventMgr = nullptr;
    CollisionManager *collisionMgr = nullptr;

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