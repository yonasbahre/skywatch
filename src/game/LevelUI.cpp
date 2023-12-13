#include "LevelUI.h"
#include "Constants.h"
#include <chrono>

LevelUI::LevelUI(EngineObject *parent) : EngineObject(parent) {}

LevelUI::~LevelUI() {}

Renderer *LevelUI::getRenderer() {
    return &renderer;
}

void LevelUI::start() {}

void LevelUI::update() {
    using namespace std::chrono;

    milliseconds now = duration_cast<milliseconds>(
        system_clock::now().time_since_epoch()
    );
    if (now.count() > clearConsoleTime && renderer.consoleText.getIsVisible()) {
        renderer.consoleText.setIsVisible(false);
    }
}

LevelUI::LevelUIRenderer::LevelUIRenderer(LevelUI *ui) : Renderer(ui) {
    this->ui = ui;
    healthText.setText("Health: 100");
    healthText.setPos({10, 10});
    consoleText.setText("Sample Console Text");
    consoleText.setPos({10, SCREEN_HEIGHT - 10 - consoleText.getDimensions().y});
    consoleText.setText("");
}

LevelUI::LevelUIRenderer::~LevelUIRenderer() {}

void LevelUI::LevelUIRenderer::render() {
    healthText.draw();
    consoleText.draw();
}

void LevelUI::updateHealthUI(float health) {
    renderer.healthText.setText("Health: " + std::to_string((int) health));
}

void LevelUI::sendMsgToConsole(std::string msg) {
    using namespace std::chrono;
    
    renderer.consoleText.setText(msg);
    renderer.consoleText.setIsVisible(true);

    milliseconds now = duration_cast<milliseconds>(
        system_clock::now().time_since_epoch()
    );
    clearConsoleTime = now.count() + WAIT_TIME_TO_CLEAR_CONSOLE_MILLISECONDS;
}