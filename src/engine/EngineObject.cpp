#include <algorithm>
#include "Engine.h"

// Don't include "EngineObject.h" because 
// it's already included by "Engine.h"
// #include "EngineObject.h"

EngineObject::EngineObject(EngineObject *parent, bool startOnCreation) {
    this->parent = parent;
    if (startOnCreation) {
        registerAndStart();
    }
}

EngineObject::~EngineObject() {
    for (EngineObject *child : children) {
        delete child;
    }

    if (parent) {
        parent->deregisterChild(this);
    } else {
        Engine::getEngine()->deregisterGlobalObject(this);
    }
}

void EngineObject::registerAndStart() {
    if (parent) {
        parent->registerChild(this);
    } else {
        Engine::getEngine()->registerGlobalObject(this);
    }
    start();
}

void EngineObject::registerChild(EngineObject *child) {
    children.push_back(child);
}

void EngineObject::deregisterChild(EngineObject *child) {
    auto iter = std::find(children.begin(), children.end(), child);
    if (iter != children.end()) {
        children.erase(iter);
    }
}

Renderer *EngineObject::getRenderer() {
    return nullptr;
}