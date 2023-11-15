#include "Renderer.h"
#include "Engine.h"

Renderer::Renderer(EngineObject *object) {
    this->object = object;
    this->sdlRenderer = Engine::getEngine()->renderer;
}