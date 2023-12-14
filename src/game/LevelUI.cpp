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
    
    breadCountText.setText("Bread: 0");
    breadCountText.setPos({10, 20 + healthText.getDimensions().y});

    ammoCountText.setText("Ammo: 5");
    ammoCountText.setPos({
        10,
        30 + healthText.getDimensions().y + breadCountText.getDimensions().y
    });

    consoleText.setText("Sample Console Text");
    consoleText.setPos({10, SCREEN_HEIGHT - 10 - consoleText.getDimensions().y});
    consoleText.setText("");
}

LevelUI::LevelUIRenderer::~LevelUIRenderer() {}

void LevelUI::LevelUIRenderer::render() {
    healthText.draw();
    breadCountText.draw();
    ammoCountText.draw();
    consoleText.draw();
}

void LevelUI::updateHealthUI(float health) {
    renderer.healthText.setText("Health: " + std::to_string((int) health));
}

void LevelUI::updateBreadCountUI(float breadCount) {
    renderer.breadCountText.setText(
        "Bread: " + std::to_string((int) breadCount)
    );
}

void LevelUI::updateAmmoCountUI(int ammoCount) {
    renderer.ammoCountText.setText("Ammo: " + std::to_string(ammoCount));
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