#pragma once
#include <functional>
#include <unordered_set>
#include "EngineObject.h"
#include "Sprite.h"
#include "EventManager.h"
#include "Collider.h"
#include "LevelUI.h"
#include "Constants.h"
#include "Direction.h"

class Crow;

class Player : public EngineObject {
    class PlayerRenderer : public Renderer {
    public:
        PlayerRenderer(Player *object);
        ~PlayerRenderer();
        Sprite sprite = Sprite(this->sdlRenderer, "assets/player.png");

        void render();
    };
    
    EventManager *eventMgr = nullptr;
    PlayerRenderer renderer = PlayerRenderer(this);
    Collider collider = Collider(renderer.sprite);
    LevelUI &ui;

    const float speed = 1;
    const float sprintScale = 3;
    Vec2D worldPos = Vec2D(0, 0);
    Direction lastDirection = UP;

    const float MAX_HEALTH = 100;
    float health = MAX_HEALTH;

    const float STAMINA_DECREASE = 0.002f;
    const float STAMINA_INCREASE = 2.0f;
    float stamina = 5;

    float breadCount = 0;
    int ammoCount = 8;

    std::function<int(Vec2D)> getRoadSegmentOfPoint;
    std::function<void(int)> updateCurrRoadSegment;
    
    void pickupBread();
    void pickupAmmo();

    std::function<void(Direction)> fireProjectile;
    bool isSpacebarDown = false;

    void decreaseStamina();
    bool isEKeyDown = false;
    bool isFKeyDown = false;
    bool isQKeyDown = false;
    void eatBread();

    std::unordered_set<Crow*> adjacentCrows;

public:
    Player(
        EngineObject *parent,
        LevelUI &ui_,
        std::function<int(Vec2D)> getRoadSegmentOfPoint,
        std::function<void(int)> updateCurrRoadSegment,
        std::function<void(Direction)> fireProjectile
    );

    ~Player();

    Renderer *getRenderer() override;
    void start();
    void update();

    void setWorldPos(Vec2D worldPos);
    Vec2D getWorldPos();
    Vec2D getAdjustedPos();

    void decreaseHealth(float amount);

    void addToAdjacentCrows(Crow *crow);
    void removeFromAdjacentCrows(Crow *crow);
};
