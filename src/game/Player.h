#include <functional>
#include "EngineObject.h"
#include "Sprite.h"
#include "EventManager.h"

class Player : public EngineObject {
    EventManager *eventMgr = nullptr;
    const float speed = 0.2;
    const float sprintScale = 3;
    Vec2D worldPos = Vec2D(0, 0);

    std::function<int(Vec2D)> getRoadIndexOfPoint;
    std::function<void(int)> updateRoadIndex;

public:
    Player(
        EngineObject *parent,
        std::function<int(Vec2D)> getRoadIndexOfPoint,
        std::function<void(int)> updateRoadIndex
    );

    void start();
    void update();

    void setWorldPos(Vec2D worldPos);
    Vec2D getWorldPos();
};

class PlayerRenderer : public Renderer {
public:
    PlayerRenderer(Player *object);
    Sprite sprite = Sprite(this->sdlRenderer, "assets/megaman.png");

    void render();
};