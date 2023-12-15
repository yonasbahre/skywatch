#pragma once
#include "Engine.h"
#include "EngineObject.h"
#include "Sprite.h"
#include "Collider.h"
#include "Player.h"
#include "CrowField.h"
#include "LevelUI.h"

class CrowState;

class Crow : public EngineObject {
    class CrowRenderer : public Renderer {
        Crow *crow = nullptr;
    public:
        Sprite sprite = Sprite(this->sdlRenderer, "assets/crow.png");
    
        CrowRenderer(Crow *crow);
        ~CrowRenderer();
        void render();
    };

    const float SIGHTING_DISTANCE = 200;

    CrowRenderer renderer = CrowRenderer(this);
    Collider collider = Collider(renderer.sprite);

    // Determines the bounds of the sightCollider
    Sprite sightColliderSprite = Sprite(
        Engine::getEngine()->renderer, 
        "assets/1x1.png"
    );

    // If the player is inside this collider, then the crow can "see" the player
    Collider sightCollider = Collider(sightColliderSprite);
    Player &player;
    CrowField &crowField;
    LevelUI &ui;

    CrowState *state;

    std::function<void()> increaseEnemyAttackRadiuses;
    float agitation = 0;

public:
    Crow(
        EngineObject *parent,
        Vec2D const &screenTransform_,
        Player &player_,
        Vec2D startPos_,
        CrowField &crowField_,
        LevelUI &levelUI_,
        std::function<void()> increaseEnemyAttackRadiuses_
    );

    ~Crow();

    Vec2D const &screenTransform;
    std::function<void(EngineObject*)> onDestroy;
    const Vec2D startPos;
    Vec2D pos = {0, 0};

    bool canTakeAction = true;
    
    Renderer *getRenderer() override;
    void start();
    void update();

    void feed();
    void pluck();
    void caw();
    void dropPebble();

    float getAgitation();
    void setAgitation(float agitation);

    void setState(CrowState *newState);
};