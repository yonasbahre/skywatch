#include "Renderer.h"
#include "Engine.h"

Renderer::Renderer(EngineObject *object) {
    this->object = object;
    this->sdlRenderer = Engine::getEngine()->renderer;
}

void Renderer::updateGlobalPosAndRender() {
    Vec2D parentPos = {0, 0};
    if (object->parent && object->parent->renderer) {
        parentPos = object->parent->renderer->globalPos;
    }

    globalPos = pos + parentPos;
    render();
}