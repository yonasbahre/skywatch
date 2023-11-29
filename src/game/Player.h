#include <functional>
#include "EngineObject.h"
#include "Sprite.h"
#include "EventManager.h"
#include "Collider.h"

class Player : public EngineObject {
    EventManager *eventMgr = nullptr;
    Collider *collider = nullptr;

    const float speed = 0.2;
    const float sprintScale = 3;
    Vec2D worldPos = Vec2D(0, 0);

    const float maxHealth = 100;
    float health = maxHealth;

    std::function<int(Vec2D)> getRoadSegmentOfPoint;
    std::function<void(int)> updateCurrRoadSegment;

public:
    Player(
        EngineObject *parent,
        std::function<int(Vec2D)> getRoadSegmentOfPoint,
        std::function<void(int)> updateCurrRoadSegment
    );

    ~Player();

    void start();
    void update();

    void setWorldPos(Vec2D worldPos);
    Vec2D getWorldPos();

    void decreaseHealth(float amount);
};

class PlayerRenderer : public Renderer {
public:
    PlayerRenderer(Player *object);
    ~PlayerRenderer();
    Sprite sprite = Sprite(this->sdlRenderer, "assets/megaman.png");

    void render();
};