#pragma once
#include "EngineObject.h"
#include "Text.h"

class LevelUI : public EngineObject {
    class LevelUIRenderer : public Renderer {
        LevelUI *ui = nullptr;

    public:
        Text healthText = Text(
            this->sdlRenderer,
            "assets/Imperator.ttf",
            24
        );

        Text staminaText = Text(
            this->sdlRenderer,
            "assets/Imperator.ttf",
            24
        );

        Text breadCountText = Text(
            this->sdlRenderer,
            "assets/Imperator.ttf",
            24
        );

        Text ammoCountText = Text(
            this->sdlRenderer,
            "assets/Imperator.ttf",
            24
        );

        Text consoleText = Text(
            this->sdlRenderer,
            "assets/Imperator.ttf",
            24
        );

        LevelUIRenderer(LevelUI *ui);
        ~LevelUIRenderer();

        void render();
    };

    LevelUIRenderer renderer = LevelUIRenderer(this);
    
    const int WAIT_TIME_TO_CLEAR_CONSOLE_MILLISECONDS = 3000;
    long long clearConsoleTime = 0;

public:
    LevelUI(EngineObject *parent);
    ~LevelUI();

    Renderer *getRenderer() override;
    void start();
    void update();

    void updateHealthUI(float health);
    void updateStaminaUI(float stamina);
    void updateBreadCountUI(float breadCount);
    void updateAmmoCountUI(int ammoCount);
    void sendMsgToConsole(std::string msg);
};