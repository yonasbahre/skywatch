#include "Renderer.h"
#include "Engine.h"

Renderer::Renderer(EngineObject *object) {
    this->object = object;
    this->sdlRenderer = Engine::getEngine()->renderer;
}

Renderer::~Renderer() {}

void Renderer::updateGlobalPosAndRender() {
    Vec2D parentPos = {0, 0};
    if (object->parent && object->parent->getRenderer()) {
        parentPos = object->parent->getRenderer()->globalPos;
    }

    globalPos = pos + parentPos;
    render();
}