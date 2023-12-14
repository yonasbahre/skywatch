#pragma once
#include <functional>
#include "EngineObject.h"
#include "Sprite.h"
#include "EventManager.h"
#include "Collider.h"
#include "LevelUI.h"
#include "Constants.h"
#include "Direction.h"

class Player : public EngineObject {
    class PlayerRenderer : public Renderer {
    public:
        PlayerRenderer(Player *object);
        ~PlayerRenderer();
        Sprite sprite = Sprite(this->sdlRenderer, "assets/megaman.png");

        void render();
    };
    
    EventManager *eventMgr = nullptr;
    PlayerRenderer renderer = PlayerRenderer(this);
    Collider collider = Collider(renderer.sprite);
    LevelUI &ui;

    const float speed = 0.2;
    const float sprintScale = 3;
    Vec2D worldPos = Vec2D(0, 0);
    Direction lastDirection = UP;

    const float MAX_HEALTH = 100;
    float health = MAX_HEALTH;

    float breadCount = 0;
    int ammoCount = 8;

    std::function<int(Vec2D)> getRoadSegmentOfPoint;
    std::function<void(int)> updateCurrRoadSegment;
    
    void pickupBread();
    void pickupAmmo();

    std::function<void(Direction)> fireProjectile;
    bool isSpacebarDown = false;

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

    void decreaseHealth(float amount);
};
