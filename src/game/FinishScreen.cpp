#include "FinishScreen.h"
#include "LevelDirectory.h"
#include "Constants.h"
#include "Engine.h"

FinishScreen::FinishScreen() {
    eventMgr = EventManager::getManager();
}

FinishScreen::~FinishScreen() {}

Renderer *FinishScreen::getRenderer() {
    return &renderer;
}

void FinishScreen::start() {}

void FinishScreen::update() {
    if (eventMgr->keyStates[SDL_SCANCODE_SPACE]) {
        Engine::getEngine()->loadLevel(START_SCREEN);
    }
}

FinishScreen::FinishScreenRenderer::FinishScreenRenderer(FinishScreen *object) 
    : Renderer(object) {
    youMadeIt.setText("You made it!");
    youMadeIt.setIsCentered(true);
    youMadeIt.setPos(globalPos + Vec2D(
        (SCREEN_WIDTH / 2),
        (SCREEN_HEIGHT / 2) - 100
    ));

    pressToReturn.setText("Press space to return to start screen");
    pressToReturn.setIsCentered(true);
    pressToReturn.setPos(globalPos + Vec2D(
        (SCREEN_WIDTH / 2),
        (SCREEN_HEIGHT / 2) + 100
    ));
}

FinishScreen::FinishScreenRenderer::~FinishScreenRenderer() {}

void FinishScreen::FinishScreenRenderer::render() {
    youMadeIt.draw();
    pressToReturn.draw();
}