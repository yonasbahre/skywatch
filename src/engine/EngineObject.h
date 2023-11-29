#pragma once
#include <vector>
#include "Renderer.h"

class EngineObject {    
public:
    EngineObject *parent = nullptr;
    std::vector<EngineObject*> children;

    EngineObject(
        EngineObject *parent = nullptr, 
        bool startOnCreation = false
    );
    virtual ~EngineObject();

    void registerAndStart();
    void registerChild(EngineObject *child);
    void deregisterChild(EngineObject *child);
    
    virtual Renderer *getRenderer();

    virtual void start() = 0;
    virtual void update() = 0;
};