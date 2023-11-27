#include <functional>
#include "EngineObject.h"
#include "Player.h"
#include "LevelMap.h"
#include "Enemy.h"

class Level1 : public EngineObject {
    const Vec2D baseScreenTransform = 
        Vec2D(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    Vec2D screenTransform = baseScreenTransform;

    Player player = Player(
        this,
        getRoadSegmentOfPoint(),
        updateCurrRoadSegment()
    );
    LevelMap map = LevelMap(this, screenTransform);
    
    std::vector<std::vector<EngineObject*>> segments;
    int currSegment = 0;
    const int LEFT_WINDOW_SIZE = 2;
    const int RIGHT_WINDOW_SIZE = 2;

    void loadSegment(int index);
    void unloadSegment(int index);

    std::function<int(Vec2D)> getRoadSegmentOfPoint();
    std::function<void(int)> updateCurrRoadSegment();

    Enemy sampleEnemy = Enemy(this, screenTransform);

public:
    Level1();
    ~Level1();

    void start();
    void update();
};