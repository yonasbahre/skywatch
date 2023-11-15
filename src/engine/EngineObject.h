#pragma once
#include <vector>
#include "Renderer.h"

class EngineObject {    
public:
    EngineObject *parent = nullptr;
    std::vector<EngineObject*> children;
    Renderer *renderer = nullptr;

    EngineObject(
        EngineObject *parent = nullptr, 
        bool startOnCreation = false
    );
    ~EngineObject();

    void registerAndStart();
    void registerChild(EngineObject *child);
    void deregisterChild(EngineObject *child);

    virtual void start() = 0;
    virtual void update() = 0;
};