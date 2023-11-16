#include <SDL2/SDL.h>
#include "EngineObject.h"
#include "Constants.h"

class LevelMap : public EngineObject {
    const Vec2D baseScreenTransform = 
        Vec2D(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

public:
    Vec2D screenTransform = baseScreenTransform;

    LevelMap(EngineObject *parent);

    void start();
    void update();

    void updateScreenTransform(Vec2D playerWorldPos);
};

class LevelMapRenderer : public Renderer {
    SDL_Color GRASS = {20, 60, 20};
    SDL_Color DIRT = {80, 80, 20};

public:
    LevelMapRenderer(LevelMap *object);
    void render();
};