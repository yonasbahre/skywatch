#include "LevelDirectory.h"
#include "StartScreen.h"
#include "Level1.h"

void registerLevels(Engine *engine) {
    using std::function;

    function<EngineObject*()> startScreenConstructor = [=]() {
        return new StartScreen();
    };
    engine->registerLevel(START_SCREEN, startScreenConstructor);
    
    function<EngineObject*()> level1Constructor = [=]() {
        return new Level1();
    };
    engine->registerLevel(LEVEL_1, level1Constructor);

    engine->setStartLevel(START_SCREEN);
}