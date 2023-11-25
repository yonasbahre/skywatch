#include <functional>
#include "EngineObject.h"
#include "Player.h"
#include "LevelMap.h"

class Level1 : public EngineObject {
    Player player = Player(
        this,
        getRoadIndexOfPoint(),
        updateRoadIndex()
    );
    LevelMap map = LevelMap(this);
    int roadIndex = 0;

    std::function<int(Vec2D)> getRoadIndexOfPoint();
    std::function<void(int)> updateRoadIndex();

public:
    Level1();
    ~Level1();

    void start();
    void update();
};