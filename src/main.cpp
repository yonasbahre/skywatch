#include "engine/Engine.h"
#include "game/LevelDirectory.h"

int main(int argc, char **argv) {
    Engine *engine = Engine::getEngine();
    registerLevels(engine);
    return engine->run();
}
