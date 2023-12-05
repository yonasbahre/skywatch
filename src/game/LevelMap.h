#include <SDL2/SDL.h>
#include "EngineObject.h"
#include "Constants.h"

class LevelMap : public EngineObject {
    class LevelMapRenderer : public Renderer {
        SDL_Color GRASS = {20, 60, 20};
        SDL_Color DIRT = {80, 80, 20};
        LevelMap *lvlMap = nullptr;

        void renderRoad(std::vector<float>& road);

    public:
        LevelMapRenderer(LevelMap *object);
        void render();
    };
    
    LevelMapRenderer renderer = LevelMapRenderer(this);
    void generateRoads();

    Vec2D startPoint = Vec2D(0, 0);
    Vec2D endPoint = Vec2D(0, 0);

public:
    const float MIN_TOTAL_DIST = 50000;
    const float MAX_TOTAL_DIST = 90000;

    const float MIN_SEGMENT_DIST = 800;
    const float MAX_SEGMENT_DIST = 2000;

    LevelMap(EngineObject *parent, Vec2D const &screenTransform);
    ~LevelMap();

    Vec2D const &screenTransform;
    const float ROAD_WIDTH = 600;
    std::vector<std::vector<float>> roadCoords; 
    // = {
    //     {0, 0, 0, 500},
    //     {0, 500, 750, 500},
    //     {750, 500, 750, 1500}
    // };

    Renderer *getRenderer() override;
    void start();
    void update();
};
