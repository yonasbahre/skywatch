#include "LevelDirectory.h"
#include "StartScreen.h"

void registerLevels(Engine *engine) {
    using std::function;

    function<EngineObject*()> startScreenConstructor = [=]() {
        return new StartScreen();
    };
    engine->registerLevel(START_SCREEN, startScreenConstructor);
    
    engine->setStartLevel(START_SCREEN);
}