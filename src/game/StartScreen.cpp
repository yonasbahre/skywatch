#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#include "Constants.h"
#include "StartScreen.h"
#include "Engine.h"
#include "Renderer.h"
#include "LevelDirectory.h"

StartScreen::StartScreen() {
    eventMgr = EventManager::getManager();
}

StartScreen::~StartScreen() {
    isFlashing = false;
    SDL_WaitThread(flasherThread, nullptr);
}

Renderer *StartScreen::getRenderer() {
    return &renderer;
}

void StartScreen::start() {
    flasherThread = SDL_CreateThread(
        flashPressStartText,
        "flasher",
        this
    );
}

void StartScreen::update() {
    if (eventMgr->keyStates[SDL_SCANCODE_RETURN]) {
        isFlashing = false;
        Engine::getEngine()->loadLevel(LEVEL_1);
    }
}

StartScreen::StartScreenRenderer::StartScreenRenderer(StartScreen *object)
    : Renderer(object) {
    title.setText("Skywatch");
    title.setIsCentered(true);
    title.setPos(globalPos + Vec2D(
        (SCREEN_WIDTH / 2),
        (SCREEN_HEIGHT / 2) - 100
    ));

    pressToStart.setText("Press enter to start");
    pressToStart.setIsCentered(true);
    Vec2D startDimensions = pressToStart.getDimensions();
    pressToStart.setPos(globalPos + Vec2D(
        (SCREEN_WIDTH / 2),
        (SCREEN_HEIGHT / 2) + 100
    ));
}

StartScreen::StartScreenRenderer::~StartScreenRenderer() {}

void StartScreen::StartScreenRenderer::render() {
    title.draw();
    pressToStart.draw();
}

// Stupid hack because you can't start an SDL thread with an
// instance method. I refuse to use Win32 threads
int StartScreen::flashPressStartText(void *data) {
    StartScreen *thisScreen = static_cast<StartScreen*>(data);
    thisScreen->togglePressStartVisibility();
    return 0;
}

void StartScreen::togglePressStartVisibility() {
    while (isFlashing) {
        renderer.pressToStart.setIsVisible(
            !renderer.pressToStart.getIsVisible()
        );
        SDL_Delay(750);
    }
}