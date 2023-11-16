#include "EngineObject.h"
#include "Sprite.h"
#include "EventManager.h"

class Player : public EngineObject {
    EventManager *eventMgr = nullptr;
    const float speed = 0.1;
    Vec2D worldPos = Vec2D(0, 0);

public:
    Player(EngineObject *parent);

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